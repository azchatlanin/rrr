#pragma once

#include <ncurses.h>

#include "system/config.hpp"

namespace rrr
{
  class menu 
  {
    public:
      menu(std::string, char, m_menu);

      std::string text;
      int start_x;
      char trigger;
      m_menu items;
      m_menu::iterator selected_item;

      void selected_next();
      void selected_prew();
  };
}
