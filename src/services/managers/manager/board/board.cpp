#include "board.hpp"

namespace rrr
{
  board::board(std::initializer_list<int> keys, std::string t) : MAIN_KEYS { keys }, title { t }
  {}

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
