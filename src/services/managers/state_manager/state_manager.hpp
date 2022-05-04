#pragma once

#include <filesystem>
#include <optional>
#include <unordered_map>

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
      // установка текущего рабочего пространства
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
      // текущее выбранное рабочее пространство
      int cmd = 'F';
      // текущая виртуальная дирректория расположения пользователя, она может отличается от его расположения в терминале по факту
      std::filesystem::path PWD;
  };
}

namespace buffer
{
  struct opt_path_hash {
    std::size_t operator()(const std::optional<std::filesystem::path>& path) const {
      return path ? std::filesystem::hash_value(path.value()) : 0;
    }
  };
  // данный буфер позволяетпо ключу найти состояние history и preview
  inline std::unordered_map<std::filesystem::path, std::filesystem::path, opt_path_hash> state;
}
