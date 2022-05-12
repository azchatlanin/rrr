#pragma once

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

      void execute(event e, std::any data) const override;
      void draw() ;
      void trigger(int key);

    private: 
      std::vector<std::shared_ptr<board>> boards;
  };
}
