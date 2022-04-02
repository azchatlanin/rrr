#pragma once

#include <map>
#include <ncurses.h>
#include "services/managers/manager.hpp"

namespace rrr
{
  struct menu_item
  {
    std::string title;
    std::string cmd;
    bool is_selected = false;
  };

  class menu_bar : public board
  {
    using m_items = std::vector<menu_item>;
    using m_menu = std::vector<std::pair<menu_item, m_items>>;

    public:
      menu_bar();

    public:
      void draw() override;
      void trigger() override;
      void commit(event) override;

    private:
      void create_win() override;

    private:
      void fill_menu();
      void draw_submenu(m_items, int);
      void set_menu_title(int, int, std::string, int);

    private:
      m_menu main_menu;
      bool on_this = false;
      int current_select_pos = 0;
      const std::map<std::string, std::string> possible_state { { "File", "F" }, { "View", "V" } };
  };
}
