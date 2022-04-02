#include "browser.hpp"

namespace rrr
{
  browser::browser()
  {
    create_win();
  };
  
  void browser::create_win()
  {
    getmaxyx(stdscr, height, width);
    state_manager::instance().get()->max_y = height;
    state_manager::instance().get()->max_x = width;

    width -= width / 7;

    win = newwin(height, width, start_y, start_x);
    box(win, 0 , 0);	
    wrefresh(win);
  }

  void browser::draw()
  {
  }

  void browser::trigger()
  {
  }

  void browser::commit(event e)
  {
    switch (e) {
      case event::rebuild_browser:
        rebuild();
      default: 
        wrefresh(win);
    }
  }
}
