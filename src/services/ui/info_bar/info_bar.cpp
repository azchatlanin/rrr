#include "info_bar.hpp"

#include "utils/utils.hpp"

namespace rrr
{

  info_bar::info_bar()
  {
    title = " Info ";    
    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    PWD = hack::utils::exec("pwd");
    PWD.erase(std::remove(PWD.begin(), PWD.end(), '\n'), PWD.end());

    win = newwin(max_y / 7, max_x / 2, max_y - max_y / 7, ft.start_x);
    box(win, 0, 0);

    set_title();
    wrefresh(win);
  }

  void info_bar::draw()
  {
    wmove(win, 1, 1);
    wclrtoeol(win);
    box(win, 0, 0);

    mvwaddstr(win, 1, 1, std::string(" path: " + PWD).c_str());

    wrefresh(win);
  }

  void info_bar::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void info_bar::trigger(int key)
  {
  }

  void info_bar::execute(event e, std::any data)
  {
    switch (e)
    {
      case CHANGE_PWD:
        PWD = std::any_cast<std::string>(data);
        break;
    }
  }
}
