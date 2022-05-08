#include "command_line.hpp"

#include "logger/logger.hpp"

#include "utils/config.hpp"

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
    move(LINES - 2, cmd.size() + 1);

    mvwaddstr(win, 1, 1, std::string(cmd).c_str());
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
        cmd = ":";
        break;
      case config::key::TAB:
        auto_fill();
        break;
      case config::key::ENTER:
        cmd = ":";
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
  }

  void command_line::drop() 
  {
    cmd = "";
  }

  void command_line::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
