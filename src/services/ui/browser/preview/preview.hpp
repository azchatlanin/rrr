#pragma once

#include <curses.h>

#include "../file/file.hpp"
#include "services/managers/manager/manager.hpp"
#include "utils/config.hpp"

namespace rrr
{
  class preview
  {
    public:
      preview(WINDOW*, int, int, int, int);

    public:
      void draw();
      void fill();

    public: 
      std::shared_ptr<WINDOW> win;

    private:
      int select_pos = 0;
      file_utils::files current_files;
      bool is_last = false;
      std::filesystem::path pwd;

    private: 
      void set_cursor_pos();
      void dirs_draw();
  };
}