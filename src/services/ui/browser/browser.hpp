#pragma once

#include <curses.h>
#include <memory>
#include <vector>

#include "services/managers/manager.hpp"

namespace rrr
{
  class browser : public board
  {
    public:
      browser();

    public:
      void draw() override;
      void trigger() override;
      void commit(event) override;

    private: 
      void create_win() override;
  };
}
