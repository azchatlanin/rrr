#pragma once

#include <unordered_map>
#include <ncurses.h>
#include "services/manager/manager.hpp"
#include "system/config.hpp"

namespace rrr
{

  struct menu_item
  {
    std::string title;
    int cmd;
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
      void rebuild() override;
      void trigger(int) override;
      void commit(event) override;

    private:
      void create_win() override;

    private:
      void fill_menu();
      void draw_submenu(m_items, int);
      void set_menu_title(int, int, std::string, int);

    private:
      m_menu main_menu;
      int cmd;

  };
}
