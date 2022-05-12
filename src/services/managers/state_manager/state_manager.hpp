#pragma once

#include <ncurses.h>
#include <filesystem>
#include <optional>
#include <vector>
#include <unordered_map>

#include "utils/config.hpp"

/*
 Данный клас определяет глобальное состояние некоторых параметров.
 например: 
 - максимальные размеры терминала
 - текущую нажатую клавишу, которую неоходимо знать в других окнах. (типа leader в vim)
*/
namespace rrr
{
  struct state_manager
  {
    // установка текущего рабочего пространства
    template<typename T>
    bool set(T key)
    {
      bool result = false;
      if (key == config::key::ESC)
      {
        cmd = 'F';
        curs_set(0);
        result = true;
      }
      
      if (cmd != ':')
        switch (key) 
        {
          case 'F':
            cmd = key;
            result = true;
            break;
          case 'V':
            cmd = key;
            result = true;
            break;
          case ':':
            cmd = key;
            curs_set(1);
            result = true;
            break;
        }

      return result;
    }

    static state_manager& instance();

    int max_y;
    int max_x;
    // текущее выбранное рабочее пространство
    int cmd = 'F';
    // текущая виртуальная дирректория расположения пользователя, она может отличается от его расположения в терминале по факту
    std::filesystem::path PWD; 
    // буфер путей к файлам с которыми массово что-то сделать
    std::vector<std::filesystem::path> buffer_path;

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
