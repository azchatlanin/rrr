#pragma once

#include <ncurses.h>

#include "tools/src/logger/logger.hpp"

#include "system/config.hpp"

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

namespace rrr
{
  class menu 
  {
    public:
      menu(std::string text, char trigger, m_menu items);
      ~menu() = default;

      std::string text;
      int start_x;
      char trigger;

      m_menu items;
      m_menu::iterator selected_item;

      void selected_next();
      void selected_prew();
  };

  class menu_bar
  {
    public:
      menu_bar(WINDOW* win);
      ~menu_bar() = default;
      
      WINDOW* win;
      WINDOW* menu_win;

      std::vector<menu> menus;
      int current_pos = 2;
      char selected;

      void init();
      void reset();
      void draw();
      void draw_menu(menu& m, bool is_selected);
      void draw_menu_item(const menu& m);
      void press(char c);
  };
}
