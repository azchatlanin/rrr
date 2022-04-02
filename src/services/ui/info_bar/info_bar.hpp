#pragma once

#include <ncurses.h>
#include "services/manager/manager.hpp"

namespace rrr
{
  class info_bar : public board
  {
    public:
      info_bar();

    public:
      void draw() override;
      void trigger(int) override;
      void commit(event) override;

    private:
      std::string title = " Info ";

    private:
      void create_win() override;
  };
}
