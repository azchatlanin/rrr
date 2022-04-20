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
      void trigger(int) override;
      void execute(event, std::any) override;

    public: 
      WINDOW* win;

    private:
      std::string PWD;

    private:
      void set_title();
  };
}
