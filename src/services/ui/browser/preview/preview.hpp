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
      file_utils::files get_current_files();
      std::string get_file_content();
      int get_cursor_pos();

    private:
      int cursor_pos = 0;
      file_utils::files current_files;
      bool is_last = false;
      std::string file_content;

    private: 
      void set_cursor_pos();
      void dirs_draw();
      void file_draw();
      void draw_empty_dir();
  };
}
