#pragma once

#include <memory>

#include "utils/convert.hpp"
#include "utils/config.hpp"

/*
 Даннфй клас определяет глобальное состояние некоторых параметров.
 например: 
 - максимальные размеры терминала
 - текущую нажатую клавишу, которую неоходимо знать в других окнах. (типа leader в vim)
*/
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

      static state_manager& instance();

    public:
      int max_y;
      int max_x;
      int cmd = 'F';
      std::string PWD;
  };
}
