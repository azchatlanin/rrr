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
    Files files(tmp.size());

    // 1. only dir with .
    // 2. only dir
    // 3. only files with .
    // 4. only files

    //std::sort(files.begin(), files.end());
    for(auto& f : files)
      mvwaddstr(win, &f - files.data(), 10, f.name.c_str());
    wrefresh(win);

    // HERE: sort vector
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
