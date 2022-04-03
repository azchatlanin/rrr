#include "browser.hpp"

#include <iterator>

namespace rrr
{

  browser::browser()
  {
    create();
  };
  
  void browser::create()
  {
    title = " File browser ";    

    getmaxyx(stdscr, height, width);
    state_manager::instance().get()->max_y = height;
    state_manager::instance().get()->max_x = width;

    width -= width / 7;

    win = newwin(height, width, start_y, start_x);
    box(win, 0 , 0);	
    set_title();

    win_history = derwin(win, height - 2, width / 3, 1, 1);

    win_navigation = derwin(win, height - 2, width / 3 + 1, 1, width / 3);
    wborder(win_navigation, '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t');	
    keypad(win_navigation, true);

    win_preview = derwin(win, height - 2, width / 3 - 1, 1, width * 2 / 3);

    wrefresh(win);
    wrefresh(win_history);
    wrefresh(win_navigation);
    wrefresh(win_preview);
  }

  void browser::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void browser::draw()
  {
    auto tmp = get_files_struct(".");
    Files result;
    Files result_files;

    std::copy_if(tmp.begin(), tmp.end(), std::back_inserter(result), [&result_files](const File& entry) -> bool { 
      if (entry.type == config::type::FILE_TYPE::DIR)
        return true;
      else
      {
        result_files.push_back(entry);
        return false;
      }
    });

    std::sort(result_files.begin(), result_files.end());
    std::sort(result.begin(), result.end());
    result.insert(result.end(), result_files.begin(), result_files.end());

    for(auto& f : result)
      mvwaddstr(win_navigation, &f - result.data() + 1, 2, f.name.c_str());
    wrefresh(win_navigation);
  }

  void browser::trigger()
  {
  }

  Files browser::get_files_struct(const std::string path)
  {
    Files f;
    std::filesystem::path p(path);
    std::filesystem::directory_iterator start(p);
    std::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(f), filesystem_convert());
    return f;
  }

  void browser::rebuild()
  {
    werase(win);
    box(win, 0 , 0);	// ??? it's don't be here
    wrefresh(win); 
  };
}
