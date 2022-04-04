#pragma once

#include <ncurses.h>
#include "services/managers/manager.hpp"

namespace rrr
{
  class info_bar : public board
  {
    public:
      info_bar();

    public:
      void draw() override;
      void trigger(std::string) override;

    public: 
      WINDOW* win;

    private:
      void create() override;
      void rebuild();
  };
}
