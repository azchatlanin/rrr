#pragma once

#include <memory>

#include "utils/convert.hpp"

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
            main_state = key;
            break;
          case 'V':
            cmd = utils::char_to_str(key);
            main_state = key;
            break;
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
      std::string main_state = "";

  };
}
