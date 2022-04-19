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
  class preview : public board
  {
    public:
      preview(WINDOW*, int, int, int, int);

    public:
      void draw() override;
      void trigger(int) override;
      void set_pwd(std::string);
      void set_pos(std::string);

    public: 
      WINDOW* win;

    private: 
      void set_title();
      void fill(bool, WINDOW*, std::string);
      void sort();
      Files get_files_struct(const std::string);

    private:
      WINDOW* parent_win;
      std::string PWD;
      std::string PWD_PREV; 
      int height, width;

      Files current_files;
  };
}
