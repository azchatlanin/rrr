#pragma once

#include <ncurses.h>

#include "services/managers/manager/manager.hpp"
#include "services/managers/state_manager/state_manager.hpp"

namespace rrr
{
  class info_bar : public board
  {
    public:
      info_bar();

    public:
      void draw() override;
      void trigger(int) override;
      void execute(event, std::any) override;

    public: 
      WINDOW* win;

    private:
      std::filesystem::path pwd;
      std::filesystem::path space_pwd;
      std::filesystem::space_info space_info;

    private:
      void set_title();
      void get_space_info();
      void clear();
  };
}
