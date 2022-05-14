#include "command_line.hpp"

#include "logger/logger.hpp"

#include "utils/config.hpp"

// hack
#include "utils/utils.hpp"
#include "string/string.hpp"

namespace rrr
{
  command_line::command_line()
  {
    MAIN_KEYS = { ':' };
    title = " :command ";

    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    win = newwin(3, max_x, max_y - 3, 0);
    box(win, 0, 0);
    set_title();

    wrefresh(win);
  }

  void command_line::draw()
  {
    // перемещение виртуального курсора в самом окне
    wmove(win, 1, 1);
    clear();

    // перемещение физического курсора, тот который мигает
    move(LINES - 2, cmd.size() + 2);

    mvwaddstr(win, 1, 1, std::string(!on_this() ? "" : ":" + cmd).c_str());
    wrefresh(win);
  }

  void command_line::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void command_line::trigger(int key)
  {
    if (!on_this()) return;
   
    switch (key) 
    {
      case config::key::TAB:
        auto_fill();
        break;
      case config::key::ENTER:
        command_run();
        break;
      case config::key::BACKSPACE:
        remove_last();
        break;
      default: 
        cmd.push_back(key);
    }
  }

  std::string command_line::get_cmd()
  {
    return cmd;
  }

  void command_line::auto_fill()
  {
    auto it = std::find_if(commands.begin(), commands.end(), [&](const std::string& c) {
      auto n = c.find(cmd);
      if (n == std::string::npos || n != 0)
        return false;
      return true;
    });

    if (it != std::end(commands)) cmd = it->data();
  }

  void command_line::execute(event e, std::any data)
  {
    switch (e)
    {
      case DROP:
        drop();
        break;
      default:
        break;
    }
  }

  void command_line::remove_last()
  {
    if(!cmd.empty())
      cmd.pop_back();
  }

  void command_line::drop() 
  {
    cmd.clear();
  }

  void command_line::command_run()
  {
    v_cmd = hack::string::split_str(cmd, ' ');
    if (v_cmd.empty()) return;

    if (v_cmd.at(0) == std::string("rename"))
      rename();
    if (v_cmd.at(0) == std::string("paste"))
      paste();
    if (v_cmd.at(0) == std::string("touch"))
      create("touch ");
    if (v_cmd.at(0) == std::string("trash"))
      remove("trash ");
    if (v_cmd.at(0) == std::string("mkdir"))
      create("mkdir -p ");
    if (v_cmd.at(0) == std::string("delete"))
      remove("rm -rf ");
    if (v_cmd.at(0) == std::string("move"))
      moving();
    if (v_cmd.at(0) == std::string("qa"))
      BOARD->execute(event::QUIT, true);
    else 
      BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::create(std::string unix_cmd)
  {
    if (v_cmd.size() < 2) return;
    auto name = std::filesystem::path(v_cmd.at(1));
    auto pwd = state_manager::instance().PWD;
    auto path = destination(pwd / name);
    hack::utils::exec(unix_cmd + path.string());
    BOARD->execute(event::COMMAND_CREATED_COMPLETED, path);
  }

  void command_line::rename()
  {
    if (v_cmd.size() < 2) return;

    auto pwd = state_manager::instance().PWD;
    auto old_name = buffer::state[pwd].filename();
    auto new_name = std::filesystem::path(v_cmd.at(1));

    if (new_name.empty()) 
    {
      BOARD->execute(event::COMMAND_COMPLETED, true);
      return; 
    }
    new_name = destination(pwd / new_name);
    hack::utils::exec("mv " + (pwd / old_name).string() + " " + new_name.string());
    buffer::state[pwd] = new_name;
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  // если файл/дир существует, то ве равно создаем но с измененным именем по милдисекундам
  std::filesystem::path command_line::destination(const std::filesystem::path f)
  {
    std::filesystem::path ds = f;

    if (std::filesystem::exists(ds)) 
    {
      std::string file_name = f.filename().string() + "_" +  std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
      ds = f.parent_path() / std::filesystem::path(file_name);
    }
    return ds;
  }

  void command_line::moving()
  {
    auto&& bfp = state_manager::instance().buffer_path;
    auto pwd = state_manager::instance().PWD;

    if (bfp.empty() || pwd.empty()) return;

    for (auto&& p : bfp)
    {
      std::string unix_cmd = "mv ";
      unix_cmd = unix_cmd + p.string() + " " + destination(state_manager::instance().PWD / p.filename()).string();
      hack::utils::exec(unix_cmd);
    }

    BOARD->execute(event::COMMAND_PASTE_COMPLETED, bfp.at(state_manager::instance().buffer_path.size() - 1));
    bfp.clear();
  }

  void command_line::paste()
  {
    auto&& bfp = state_manager::instance().buffer_path;
    auto pwd = state_manager::instance().PWD;

    if (bfp.empty() || pwd.empty()) return;

    for (auto&& p : bfp)
    {
      std::string unix_cmd = std::filesystem::is_directory(p) ? "cp -R " : "cp ";
      unix_cmd = unix_cmd + p.string() + " " + destination(state_manager::instance().PWD / p.filename()).string();
      hack::utils::exec(unix_cmd);
    }

    BOARD->execute(event::COMMAND_PASTE_COMPLETED, bfp.at(state_manager::instance().buffer_path.size() - 1));
    bfp.clear();
  }

  void command_line::remove(std::string unix_cmd)
  {
    auto bfp = state_manager::instance().buffer_path;

    if (bfp.size() != 0)
      for (auto&& p : bfp)
        hack::utils::exec(unix_cmd + p.string());
    else 
      hack::utils::exec((unix_cmd + buffer::state[state_manager::instance().PWD].string()));

    BOARD->execute(event::COMMAND_REMOVE_COMPLETED, true);
  }

  void command_line::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
