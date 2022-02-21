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
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    getmaxyx(stdscr, height, width);

    win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);

    std::string menu1[] = { "menu1-1", "menu1-2" };
    std::string menu2[] = { "menu2-1", "menu2-2" };

    std::vector<menu> menus = { 
      menu{ "File", 'F', menu1, 2 }, 
      menu{ "Edit", 'E', menu2, 2 }, 
    };

    menu_bar mb = menu_bar(win, std::move(menus));
    mb.init();
    mb.draw();

    while(char ch = wgetch(win))
    {
      mb.press(ch);
      mb.draw();
    }
  }
}
