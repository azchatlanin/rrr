#include "system_bar.hpp"

#include "utils/utils.hpp"

namespace rrr
{
  system_bar::system_bar() : board { 'S' }
  {
    title = " System ";    
    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    win = newwin(max_y / 7 - 3, max_x / 2, max_y - max_y / 7, ft.start_x + max_x / 2);
    box(win, 0, 0);
    set_title();

    wrefresh(win);
  }

  void system_bar::draw()
  {
    mvwaddstr(win, 1, 1, "adf");
    wrefresh(win);
  }

  void system_bar::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void system_bar::trigger(int key)
  {
    if (!on_this()) return;
  }

  void system_bar::execute(event e, std::any data)
  {
  }

  void system_bar::drop() 
  {}

  void system_bar::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
