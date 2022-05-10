#pragma once

#include <curses.h>

#include "../file/file.hpp"
#include "services/managers/manager/manager.hpp"
#include "utils/config.hpp"

namespace rrr
{
  class navigation
  {
    public:
      navigation(WINDOW*, int, int, int, int);

    public:
      void draw();
      void fill();
      //@annotation
      // две перегруженные функции для установки позиции курсора
      // первая ставит по индексу, вторая при перехоже на другую страницу
      void set_cursor_pos(int);
      void set_cursor_pos();
      void buffer_update();
      void select();

    public: 
      std::shared_ptr<WINDOW> win;

    private:
      int select_pos = 0;
      file_utils::files current_files;
      bool is_last = false;
      std::filesystem::path file_name;
  };
}
