#pragma once

#include "services/managers/manager/manager.hpp"

#include "utils/config.hpp"

#include "history/history.hpp"
#include "navigation/navigation.hpp"
#include "preview/preview.hpp"

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
      void drop() override;

    public: 
      WINDOW* win;
      std::shared_ptr<history> win_history;
      std::shared_ptr<navigation> win_navigation;
      std::shared_ptr<preview> win_preview;

    private: 
      void set_title();
      void next();
      void prew();
      void move(int);
      void refresh();
      void erise();
      void update();

    private:
      int key;
      int select_pos = 0;
  };
}
