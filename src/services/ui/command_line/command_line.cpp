#include "command_line.hpp"

#include "logger/logger.hpp"

#include "utils/config.hpp"

// hack
#include "utils/utils.hpp"
#include "string/string.hpp"

namespace rrr
{

  command_line::command_line() : board { { 'C', ':' }, " :Command " }
  {
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
      case config::key::COLON_COLON:
        cmd = "";
        break;
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

  // HERE
  // при массовом копировании появляется лишний файл
  // перенести выбор при копировании и перемещении в буфер
  //
  // сдеать массовое копирование
  // сдеать массовое удаление
  // сделать массовое перемещение
  // при нажатии на esc снять все выделения
  void command_line::command_run()
  {
    v_cmd = hack::string::split_str(cmd, ' ');
    if (v_cmd.empty()) return;

    if (v_cmd.at(0) == std::string("rename"))
      rename();
    if (v_cmd.at(0) == std::string("copy"))
      copy();
    if (v_cmd.at(0) == std::string("paste"))
      paste();
    if (v_cmd.at(0) == std::string("touch"))
      create("touch ");
    if (v_cmd.at(0) == std::string("trash"))
      trash();
    if (v_cmd.at(0) == std::string("mkdir"))
      create("mkdir -p ");
    if (v_cmd.at(0) == std::string("delete"))
      rm_rf();
  }

  void command_line::create(std::string unix_cmd)
  {
    if (v_cmd.size() < 2) return;
    auto name = std::filesystem::path(v_cmd.at(1));
    if (!name.empty()) BOARD->execute(event::COMMAND_COMPLETED, true); 
    hack::utils::exec((unix_cmd + (state_manager::instance().PWD / name).string()).c_str());
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::rename()
  {
    if (v_cmd.size() < 2) return;
    auto old_name = buffer::state[state_manager::instance().PWD].filename();
    auto new_name = std::filesystem::path(v_cmd.at(1));
    if (new_name.empty()) 
    {
      BOARD->execute(event::COMMAND_COMPLETED, true);
      return; 
    }
    hack::utils::exec(("mv " + (state_manager::instance().PWD /old_name).string() + " " + (state_manager::instance().PWD / new_name).string()).c_str());
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::copy()
  {
    auto name = buffer::state[state_manager::instance().PWD].filename();
    state_manager::instance().buffer_path.push_back(state_manager::instance().PWD / name);
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::paste()
  {
    for (auto&& p : state_manager::instance().buffer_path)
    {
      std::string unix_cmd = std::filesystem::is_directory(p) ? "cp -R " : "cp ";
      std::filesystem::path destination = state_manager::instance().PWD / p.filename();

      if (std::filesystem::exists(state_manager::instance().PWD / p)) 
      {
        std::string file_name = p.filename().string() + "_" +  std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        destination = state_manager::instance().PWD / std::filesystem::path(file_name);
      }

      hack::utils::exec((unix_cmd + p.string() + " " + destination.string()).c_str());
    }
    state_manager::instance().buffer_path.clear();
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::trash()
  {
    auto name = buffer::state[state_manager::instance().PWD].filename();
    hack::utils::exec(("trash " + (state_manager::instance().PWD / name).string()).c_str());
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::rm_rf()
  {
    auto name = buffer::state[state_manager::instance().PWD].filename();
    hack::utils::exec(("rm -rf " + (state_manager::instance().PWD / name).string()).c_str());
    BOARD->execute(event::COMMAND_COMPLETED, true);
  }

  void command_line::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
