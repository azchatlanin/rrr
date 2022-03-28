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
    getmaxyx(lr->win, y_max, x_max);
    getbegyx(lr->win, start_y, start_x);

    height = y_max / 6;
    width = x_max / 6;

    start_y = y_max - height;
    start_x = x_max - width;

    win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    keypad(win, true);
  }

  void info_bar::draw()
  {
    wattron(win, COLOR_PAIR(1));
    wattron(win,A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win,A_BOLD);
    wattroff(win, COLOR_PAIR(1));

    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());

    wrefresh(win);
  }
}
