#pragma once

#include <curses.h>
#include <memory>
#include <vector>

#include "services/manager/manager.hpp"

namespace rrr
{
  class browser : public board
  {
    public:
      browser();

    public:
      void draw() override;
      void trigger(int) override;
      void commit(event) override;

    private: 
      void create_win() override;
  };
}
