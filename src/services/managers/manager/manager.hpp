#pragma once

#include <vector>
#include <any>

#include "board/board.hpp"

namespace rrr
{
  class manager : public i_board
  {
    public: 
      template<typename... Args>
      explicit manager(Args&... args)
      {
        auto bi = std::back_inserter(boards);
        ((bi = args), ...);
        for (auto&& b : boards) b->set(this);
      }

      void execute(event e, std::any data) const override
      {
        for (auto&& b : boards)
        {
          b->execute(e, data);
          state_manager::instance().set(config::key::ESC);
          b->execute(event::DROP, true);
        }
      }

      void draw() 
      {
        for (auto& b : boards) b->draw();
      }

      void trigger(int key) 
      {
        state_manager::instance().set(key);

        if (key == config::key::ESC) 
        {
          for (auto&& b : boards) b->execute(event::DROP, true);
          return;
        }

        for (auto&& b : boards) b->trigger(key);
      }

    private: 
      std::vector<std::shared_ptr<board>> boards;
  };
}
