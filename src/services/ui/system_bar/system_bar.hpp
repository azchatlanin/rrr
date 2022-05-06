#pragma once

#include <ncurses.h>

#include "services/managers/manager/manager.hpp"
#include "services/managers/state_manager/state_manager.hpp"

namespace rrr
{
  class system_bar : public board
  {
    public:
      system_bar();

    public:
      void draw() override;
      void trigger(int) override;
      void execute(event, std::any) override;
      void drop() override;

    public: 
      WINDOW* win;

    private:
      void set_title();
      void clear();
  };
}
