#include "preview.hpp"

#include <curses.h>
#include <iterator>

#include "utils/utils.hpp"

namespace rrr
{

  preview::preview(WINDOW* pw, int h, int w, int pos_y, int pos_x) : parent_win { pw }, height { h } , width { w }
  {
    win = derwin(parent_win, height, width, pos_y, pos_x);
  };
  
  void preview::draw()
  {
    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      if (f.type == config::type::FILE_TYPE::DIR)
        wattron(win, COLOR_PAIR(1));
      mvwaddstr(win, i + 1, 4, f.name.c_str());
      wattroff(win, COLOR_PAIR(1));
    }
    
    wrefresh(win);
  }

  void preview::sort()
  {
    current_files = get_files_struct(PWD_PREV);
    Files tmp;
    tmp.reserve(current_files.size());
    Files tmp_files;
    tmp_files.reserve(current_files.size() / 2);

    std::copy_if(current_files.begin(), current_files.end(), std::back_inserter(tmp), [&tmp_files](const File& entry) -> bool {
      if (entry.type == config::type::FILE_TYPE::DIR)
        return true;
      else
      {
        tmp_files.push_back(entry);
        return false;
      }
    });

    std::sort(tmp_files.begin(), tmp_files.end());
    std::sort(tmp.begin(), tmp.end());
    tmp.insert(tmp.end(), tmp_files.begin(), tmp_files.end());
    current_files= tmp;
  }

  void preview::set_pwd(std::string pwd)
  {
    PWD = pwd;
  }

  void preview::set_pos(std::string p)
  {
    PWD_PREV = PWD + "/" + p;
    sort();
  }

  void preview::trigger(int k)
  {
  }
}
