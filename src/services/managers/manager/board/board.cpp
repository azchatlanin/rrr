#include "board.hpp"

namespace rrr
{
  board::board(const int main_key) : MAIN_KEY { main_key } 
  {}

  void board::set(i_board* b_) 
  { 
    BOARD = b_; 
  }

  bool board::on_this()
  {
    return  state_manager::instance().cmd == MAIN_KEY ? true : false;
  }
}
