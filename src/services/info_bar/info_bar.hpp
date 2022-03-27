#pragma once

#include <ncurses.h>
#include "layer/layer.hpp"

namespace rrr
{
  class info_bar : public board
  {
    public:
      info_bar();

    public:
      WINDOW* info_bar_win;

    public:
      static std::shared_ptr<info_bar> create();
      void draw() override;

    private:
      int start_x, start_y, width, height;

    private:
      void create_win();
  };
}
