#include "board.hpp"

#include "menu_bar/menu_bar.hpp"

namespace rrr
{
  void board::init()
  {
    initscr();
    noecho();
    curs_set(0);

    if (!has_colors()) return;
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);

    getmaxyx(stdscr, height, width);

    board_win = newwin(height, width, start_y, start_x);
    box(board_win, 0, 0);
    
    menu_bar mb = menu_bar(board_win);
    mb.init();
    mb.draw();

    while(char ch = wgetch(board_win))
    {
      mb.press(ch);
      mb.draw();
    }
  }
}
