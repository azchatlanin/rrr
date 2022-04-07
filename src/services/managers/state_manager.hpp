#pragma once

#include <memory>

#include <ncurses.h>
#include "utils/convert.hpp"
#include "utils/config.hpp"

namespace rrr
{
  class state_manager
  {
    public:
      template<typename T>
      void set(T key)
      {
        switch (key) {
          case 'F':
            cmd = key;
            break;
          case 'V':
            cmd = key;
            break;
          case 27: // ESC
            cmd = key;
            break;
        }
      }

      static state_manager& instance()
      {
        static state_manager st;
        return st;
      }

    public:
      int max_y;
      int max_x;
      int cmd = 'F';
  };
}
