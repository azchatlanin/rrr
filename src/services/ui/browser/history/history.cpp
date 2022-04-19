#include "browser.hpp"

#include <curses.h>
#include <iterator>

#include "utils/utils.hpp"

namespace rrr
{

  history::history(WINDOW* pw, int h, int w) : parent_win { pw }, height { h } , width { w }
  {
    win = derwin(parent_win, height, width, 1, 1);
  };
  
  void history::draw()
  {
    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      if (select_pos == i)
        mvwaddch(win, i + 1, 2, ACS_RARROW);
      mvwaddstr(win, i + 1, 4, f.name.c_str());
    }
    
    wrefresh(win);
  }

  void history::sort()
  {
    current_files = get_files_struct(PWD);
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

  void history::set_pwd(std::string pwd)
  {
    PWD = pwd;
    sort();
  }

  void history::set_pos(std::string p)
  {
    auto pos = p.find_last_of("/");
    auto file = p.substr(pos + 1);

    auto find_pred = [&](File f) -> bool { 
      return f.name.compare(file) == 0 ? true : false;
    };
    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    if (it != std::end(current_files))
      select_pos = it - current_files.begin();
  }

  void history::trigger(int k)
  {
  }

  Files history::get_files_struct(const std::string path)
  {
    Files f;
    std::filesystem::path p(path);
    std::filesystem::directory_iterator start(p);
    std::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(f), filesystem_convert());
    return f;
  }
}
