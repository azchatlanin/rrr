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
            cmd = utils::char_to_str(key);
            break;
          case 'V':
            cmd = utils::char_to_str(key);
            break;
          case 27: // ESC
            cmd = config::key::ESC;
          default: 
            cmd = key;
        }
      }

      static std::shared_ptr<state_manager> instance()
      {
        static std::shared_ptr<state_manager> st = std::make_shared<state_manager>();
        return st;
      }

    public:
      int max_y;
      int max_x;
      std::string cmd = "";
  };
}
