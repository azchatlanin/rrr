#pragma once

#include <ncurses.h>

#include "system/config.hpp"
#include "menu/menu.hpp"

namespace rrr
{
  class menu_bar
  {
    public:
      menu_bar(WINDOW* win);
      
    public:
      WINDOW* board_win;
      WINDOW* menu_win;
      std::vector<menu> menus;
      int current_pos;
      char selected;

    public:
      void init();
      void draw();
      void press(char c);

    private:
      void draw_menu(menu& m, bool is_selected);
      void draw_menu_item(const menu& m);
      void reset();
  };
}
