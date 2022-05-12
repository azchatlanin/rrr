#include "board.hpp"

#include <algorithm>

namespace rrr
{
  void board::set(i_board* b_) 
  { 
    BOARD = b_; 
  }

  bool board::on_this()
  {
    auto it = std::find_if(MAIN_KEYS.begin(), MAIN_KEYS.end(), [](const int v) {
      return v == state_manager::instance().cmd;
    });

    return it != std::end(MAIN_KEYS);
  }
}
