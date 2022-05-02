#include <curses.h>

namespace nc
{
  inline void init()
  {
    ::initscr();
    ::noecho();
    ::curs_set(0);
    ::cbreak();			
    ::keypad(stdscr, TRUE);
    ESCDELAY = 0;
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
