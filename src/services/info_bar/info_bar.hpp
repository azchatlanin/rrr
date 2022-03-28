#pragma once

#include <ncurses.h>
#include "services/layer/layer.hpp"

namespace rrr
{
  class info_bar : public board
  {
    public:
      info_bar();

    public:
      WINDOW* win;

    public:
      static std::shared_ptr<info_bar> create();
      void draw() override;

    private:
      int start_x, start_y, width, height;
      std::string title = " Info ";

    private:
      void create_win() override;
  };
}
