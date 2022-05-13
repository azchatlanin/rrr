#pragma once

#include <curses.h>

#include "../file/file.hpp"
#include "services/managers/manager/manager.hpp"
#include "utils/config.hpp"

namespace rrr
{
  class history
  {
    public:
      history(WINDOW*, int, int, int, int);

    public:
      void draw();
      void fill();
      int get_cursor_pos();
      file_utils::files get_current_files();

    public: 
      std::shared_ptr<WINDOW> win;

    private:
      int cursor_pos = 0;
      file_utils::files current_files;
      bool is_last = false;

    private: 
      void set_cursor_pos();
      void root_draw();
      void dirs_draw();
  };
}
