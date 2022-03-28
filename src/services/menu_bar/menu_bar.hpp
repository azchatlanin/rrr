#pragma once

#include <ncurses.h>
#include "services/layer/layer.hpp"

namespace rrr
{
  using m_menu = std::vector<std::pair<std::string, std::string>>;

  class menu_bar : public board
  {
    public:
      menu_bar();

    public:
      static std::shared_ptr<menu_bar> create();
      void draw() override;

    private:
      int start_x, start_y, width, height;

      m_menu main_menu;

    private:
      void create_win() override;
      void fill_menu();
  };
}
