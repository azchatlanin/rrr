#include "browser.hpp"

#include "logger/logger.hpp"

namespace rrr
{
  browser::browser()
  {
    create_win();
  };
  
  void browser::create_win()
  {
    getmaxyx(stdscr, height, width);
    state::instance().get()->max_y = height;
    state::instance().get()->max_x = width;

    width -= width / 7;

    win = newwin(height, width, start_y, start_x);
    box(win, 0 , 0);	
    wrefresh(win);
  }

  void browser::draw()
  {
  }

  void browser::rebuild()
  {
    destroy();
    create_win();
  }

  void browser::trigger(int key)
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
