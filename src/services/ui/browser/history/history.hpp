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
      void set_pwd();

    public: 
      std::shared_ptr<WINDOW> win;

    private:
      int select_pos = 0;
      Files current_files;
      bool is_last = false;

    private: 
      void set_pos();
      void root_draw();
      void dirs_draw();
  };
}
