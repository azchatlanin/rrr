#include <curses.h>

namespace nc
{
  inline void init()
  {
    ESCDELAY = 0;
    ::initscr();
    ::noecho();
    ::curs_set(0);
    ::cbreak();			
    ::keypad(stdscr, TRUE);
    ::refresh();
  }

  inline void refresh()
  {
    ::refresh();
  }

  inline void end()
  {
    ::endwin();
  }
}
