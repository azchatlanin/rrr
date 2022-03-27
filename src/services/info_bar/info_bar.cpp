#include "info_bar.hpp"

namespace rrr
{
  std::shared_ptr<info_bar> info_bar::create()
  {
    static std::shared_ptr<info_bar> ib(new info_bar);
    return ib;
  }

  info_bar::info_bar()
  {
    create_win();
  }

  void info_bar::create_win()
  {
    auto lr = layer::instance().get();
    int y_max, x_max;
    getmaxyx(lr->layer_win, y_max, x_max);
    getbegyx(lr->layer_win, start_y, start_x);

    height = y_max / 6;
    width = x_max / 6;

    start_y = y_max - height;
    start_x = x_max - width;

    info_bar_win = newwin(height, width, start_y, start_x);
    box(info_bar_win, 0, 0);
    
    keypad(info_bar_win, true);
    wrefresh(info_bar_win);
  }

  void info_bar::draw()
  {
  }
}
