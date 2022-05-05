#include "command_line.hpp"

#include "utils/utils.hpp"

namespace rrr
{

  command_line::command_line() : board { 'C' }
  {
    title = " Command ";    
    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    win = newwin(3, max_x, max_y - 3, 0);
    box(win, 0, 0);
    set_title();

    wrefresh(win);
  }

  void command_line::draw()
  {
    mvwaddstr(win, 1, 1, "adf");
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
  }

  void command_line::execute(event e, std::any data)
  {
  }

  void command_line::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
