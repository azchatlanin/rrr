#include "info_bar.hpp"

namespace rrr
{

  info_bar::info_bar()
  {
    title = " Info ";    
    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    ft.height = max_y / 7;
    ft.width = max_x / 7;
    ft.start_y = max_y - ft.height;
    ft.start_x = max_x - ft.width;

    win = newwin(ft.height, ft.width, ft.start_y, ft.start_x);
    box(win, 0, 0);
    keypad(win, true);
    wrefresh(win);
  }

  void info_bar::draw()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);

    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());

    wrefresh(win);
  }

  void info_bar::trigger(int key)
  {
    mvwaddstr(win, 1, 1, " press:      "); 
    mvwaddstr(win, 1, 1, std::string(" press: " + utils::key_to_str(key)).c_str());
    wrefresh(win);
  }

  void info_bar::rebuild()
  {
    werase(win);
    box(win, 0 , 0);	// ??? it's don't be here
    wrefresh(win); 
  };
}
