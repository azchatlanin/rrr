#include "info_bar.hpp"

namespace rrr
{

  info_bar::info_bar()
  {
    create();
  }

  void info_bar::create()
  {
    title = " Info ";    
    auto max_x = state_manager::instance().get()->max_x;
    auto max_y = state_manager::instance().get()->max_y;

    height = max_y / 7;
    width = max_x / 7;
    start_y = max_y - height;
    start_x = max_x - width;

    win = newwin(height, width, start_y, start_x);
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
