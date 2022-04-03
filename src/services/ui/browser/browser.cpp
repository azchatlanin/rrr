#include "browser.hpp"

#include <iterator>

namespace rrr
{

   browser::browser()
  {
    create_win();
  };
  
  void browser::create_win()
  {
    getmaxyx(stdscr, height, width);
    state_manager::instance().get()->max_y = height;
    state_manager::instance().get()->max_x = width;

    width -= width / 7;

    win = newwin(height, width, start_y, start_x);
    box(win, 0 , 0);	
    wrefresh(win);
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
      mvwaddstr(win, &f - result.data() + 2, 10, f.name.c_str());
    wrefresh(win);
  }

  void browser::trigger()
  {
  }

  void browser::commit(event e)
  {
    switch (e) {
      case event::rebuild_browser:
        rebuild();
      default: 
        wrefresh(win);
    }
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
}
