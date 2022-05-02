#pragma once

#include "services/managers/manager/manager.hpp"
#include "services/managers/state_manager/state_manager.hpp"

#include "utils/config.hpp"

#include "history/history.hpp"

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
      std::shared_ptr<history> win_history;
      std::shared_ptr<decorator> win_preview;

    private: 
      void set_title();
      void next_pwd();
      void prew_pwd();
      void up();
      void down();

    private:
      int key;
      int select_pos = 0;
      Files current_files;
  };
}
