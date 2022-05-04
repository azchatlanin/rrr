#include "info_bar.hpp"

#include "utils/utils.hpp"

namespace rrr
{

  info_bar::info_bar() : board { 'F' }
  {
    title = " Info ";    
    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    win = newwin(max_y / 7, max_x / 2, max_y - max_y / 7, ft.start_x);
    box(win, 0, 0);
    set_title();

    pwd = state_manager::instance().PWD / buffer::state[state_manager::instance().PWD];

    wrefresh(win);
  }

  void info_bar::draw()
  {
    wmove(win, 1, 1);
    clear();
    mvwaddstr(win, 1, 1, std::string(" current path: " + pwd.string()).c_str());
    wrefresh(win);
  }

  void info_bar::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void info_bar::trigger(int key)
  {
    if (!on_this()) return;
  }

  void info_bar::execute(event e, std::any data)
  {
    switch (e)
    {
      case CHANGE_PWD:
        pwd = std::any_cast<std::filesystem::path>(data);
        break;
    }
  }

  void info_bar::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
