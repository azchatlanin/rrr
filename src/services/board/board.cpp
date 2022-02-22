#include "board.hpp"

#include <map>

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

    m_menu f_menu = { { "N", "New" }, { "E", "Edit" }, { "D", "Delete" }, { "BackSpace", "Select" }, { "C", "Copy" }, { "P", "Paste" }, { "Q", "Quit" } };
    
    std::vector<menu> menus = { 
      menu { "File", 'F', std::move(f_menu) }, 
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
