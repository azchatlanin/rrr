#pragma once

#include <curses.h>
#include <memory>
#include <vector>
#include <filesystem>

#include "../file/file.hpp"
#include "services/managers/manager.hpp"
#include "utils/config.hpp"

namespace rrr
{
  class decorator
  {
    public:
      decorator(WINDOW*, int, int, int, int);

    public:
      void draw();
      void set_pwd(std::string);
      void set_pos(std::string);

    public: 
      WINDOW* win;

    private:
      WINDOW* parent_win;
      std::string PWD;
      int height, width;
      int select_pos = 0;
      Files current_files;
  };
}
