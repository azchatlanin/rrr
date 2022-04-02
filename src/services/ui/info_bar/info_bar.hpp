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
      void trigger() override;
      void commit(event) override;

    private:
      std::string title = " Info ";

    private:
      void create_win() override;
  };
}
