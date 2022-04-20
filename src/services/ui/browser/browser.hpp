#pragma once

#include <curses.h>
#include <memory>
#include <vector>
#include <filesystem>

#include "services/managers/manager.hpp"
#include "utils/config.hpp"
#include "decorator/decorator.hpp"

namespace rrr
{
  class browser : public board
  {
    public:
      browser();

    public:
      void draw() override;
      void trigger(int) override;
      void execute(event, std::any) override;

    public: 
      WINDOW* win;
      WINDOW* win_navigation;
      std::shared_ptr<decorator> win_history;
      std::shared_ptr<decorator> win_preview;

    private: 
      void set_title();
      void next_pwd();
      void prew_pwd();

    private:
      const int MAIN_KEY = 'F';
      std::string PWD;
      int key;
      int select_pos = 0;
      bool on_this = false;
      Files current_files;
  };
}
