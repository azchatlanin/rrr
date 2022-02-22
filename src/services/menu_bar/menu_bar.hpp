#pragma once

#include <map>
#include <curses.h>
#include <menu.h>

#include <panel.h>
#include <string.h>
#include "tools/src/logger/logger.hpp"

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

namespace rrr
{
  using m_menu = std::map<std::string, std::string>;

  class menu 
  {
    public:
      menu(std::string text, char trigger, m_menu&& items);
      ~menu() = default;

      int start_x;
      std::string text;
      char trigger;

      m_menu items;
      int num_items;
      int selected_item;

      void selected_next();
      void selected_prew();
  };

  class menu_bar
  {
    public:
      menu_bar(WINDOW* win, std::vector<menu>&& menus);
      ~menu_bar() = default;
      
      WINDOW* win;
      WINDOW* menu_win;

      std::vector<menu> menus;
      int current_pos = 2;
      char selected;

      void init();
      void reset();
      void draw();
      void draw_menu(menu m, bool is_selected);
      void draw_menu_item(menu m);
      void press(char c);
  };
}
