#include "decorator.hpp"

#include <curses.h>
#include <iterator>

#include "utils/utils.hpp"

namespace rrr
{

  decorator::decorator(WINDOW* pw, int h, int w, int pos_y, int pos_x) : parent_win { pw }, height { h } , width { w }
  {
    win = derwin(parent_win, height, width, pos_y, pos_x);
  };
  
  void decorator::draw()
  {
    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();

      if (f.type == config::type::FILE_TYPE::DIR)
      {
        wattron(win, COLOR_PAIR(1) | (select_pos == i ? A_BOLD : 0));
        select_pos == i ? mvwaddch(win, i + 1, 2, ACS_RARROW) : 0;
      }
      mvwaddstr(win, i + 1, 4, f.name.c_str());
      wattroff(win, COLOR_PAIR(1) | (select_pos == i ? A_BOLD : 0));
    }
    
    wrefresh(win);
  }

  void decorator::set_pwd(std::string pwd)
  {
    PWD = pwd;
    fill(current_files, PWD);
  }

  void decorator::set_pos(std::string p)
  {
    auto pos = p.find_last_of("/");
    auto file = p.substr(pos + 1);

    auto find_pred = [&](File f) -> bool { 
      return f.name.compare(file) == 0 ? true : false;
    };
    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    if (it != std::end(current_files))
      select_pos = it - current_files.begin();
    else 
      select_pos = 0;
  }
}