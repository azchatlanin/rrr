#pragma once

#include <curses.h>
#include <memory>
#include <vector>
#include <filesystem>

#include "services/managers/manager.hpp"
#include "utils/config.hpp"
#include "history/history.hpp"

namespace rrr
{
  class browser : public board
  {
    public:
      browser();

    public:
      void draw() override;
      void trigger(int) override;

    public: 
      WINDOW* win;
      std::shared_ptr<history> win_history;

      WINDOW* win_preview;
      WINDOW* win_navigation;

    private: 
      void set_title();
      void set_cursor_position(const Files&);
      void rebuild();
      void fill();
      void sort();
      void next_pwd();
      void prew_pwd();
      Files get_files_struct(const std::string);

    private:
      const int MAIN_KEY = 'F';
      std::string PWD;
      int key;
      int select_pos = 0;
      bool on_this = false;
      Files current_files;
  };
}
