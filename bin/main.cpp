#include "services/board/board.hpp"

namespace rrr
{
  inline int run()
  {
    board b;
    b.init();

    getch();
    endwin(); 
    return 0;
  }

}

int main(int argc, char **argv)
{
  return rrr::run();
}

