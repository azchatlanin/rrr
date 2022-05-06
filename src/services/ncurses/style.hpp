#include <curses.h>

namespace nc
{
  inline void init_style()
  {
    if (!has_colors()) throw "Don't set color";

    use_default_colors();
    start_color();

    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_CYAN, -1);
  }
}