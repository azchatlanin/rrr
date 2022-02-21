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
  class menu 
  {
    public:
      menu(std::string text, char trigger, std::string *items, int num_items) : text { text } , trigger { trigger }, items { items }, num_items { num_items }  {}
      int start_x;
      std::string text;
      char trigger;

      std::string* items;
      int num_items;
      int selected_item;

      void selected_next()
      {
        selected_item++;
        if (selected_item >= num_items) selected_item = 0;
      }

      void selected_prew()
      {
        selected_item--;
        if (selected_item < 0) selected_item = num_items - 1;
      }
  };

  class menu_bar
  {
    public:
      menu_bar(WINDOW* win, std::vector<menu>&& menus) : win { win }, menus { menus } {}
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
