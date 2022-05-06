#pragma once

#include <vector>
#include <ncurses.h>

#include "services/managers/manager/manager.hpp"
#include "services/managers/state_manager/state_manager.hpp"

namespace rrr
{
  class command_line : public board
  {
    public:
      command_line();

    public:
      void draw() override;
      void trigger(int) override;
      void execute(event, std::any) override;
      void drop() override;

    public: 
      WINDOW* win;

    private: 
      std::string cmd;
      std::vector<std::string> commands { ":rename", ":delete", ":copy", ":paste"};

    private:
      void set_title();
      void auto_fill();
      void clear();
  };
}
