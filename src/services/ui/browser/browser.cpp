#include "browser.hpp"

#include <curses.h>
#include <iterator>

#include "utils/utils.hpp"

namespace rrr
{

  browser::browser()
  {
    create();
  };
  
  void browser::create()
  {
    title = " File browser ";    

    PWD = hack::utils::exec("pwd");
    PWD.erase(std::remove(PWD.begin(), PWD.end(), '\n'), PWD.end());

    getmaxyx(stdscr, height, width);
    state_manager::instance().max_y = height;
    state_manager::instance().max_x = width;

    width -= width / 7;

    win = newwin(height, width, start_y, start_x);
    box(win, 0 , 0);	
    set_title();

    win_history = derwin(win, height - 2, width / 3, 1, 1);
    //wborder(win_history, '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t');	

    win_navigation = derwin(win, height - 2, width / 3 + 1, 1, width / 3);
    //wborder(win_navigation, '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t');	

    win_preview = derwin(win, height - 2, width / 3 - 1, 1, width * 2 / 3);
    //wborder(win_preview, '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t');	

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

  void browser::prew_pwd()
  {
    auto pos = PWD.find_last_of("/");
    PWD = pos ? PWD.substr(0, pos) : "/";
  }

  void browser::next_pwd(std::string name)
  {
    PWD += "/" + name;
  }

  void browser::draw()
  {
    auto pos = PWD.find_last_of("/");
    auto PWD_PREW = pos ? PWD.substr(0, pos) : "/";
    
    fill(false, win_history, PWD_PREW);
    fill(true, win_navigation, PWD);
  }

  void browser::fill(bool show_cursor, WINDOW* w, std::string p)
  {
    auto tmp = get_files_struct(p);
    Files result;
    result.reserve(tmp.size());
    Files result_files;
    result_files.reserve(tmp.size() / 2);

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

    if (show_cursor)
      set_cursor_position(result);

    for(auto&& f : result)
    {
      auto i = &f - result.data();
      if (select_pos == i)
        mvwaddch(w, i + 1, 2, ACS_RARROW);
      mvwaddstr(w, i + 1, show_cursor ? 5 : 2, f.name.c_str());
    }
    
    wrefresh(w);
  }

  void browser::set_cursor_position(const Files& result)
  {
    switch (key) 
    {
      case 'j':
        ++select_pos;
        break;
      case KEY_DOWN:
        ++select_pos;
        break;
      case 'k':
        --select_pos;
        break;
      case KEY_UP:
        --select_pos;
        break;
      default: 
        select_pos = 0;
    }
    if (select_pos <= 0) select_pos = 0;
    if (select_pos >= static_cast<int>(result.size())) select_pos = result.size() - 1;
  }

  void browser::trigger(int k)
  {
    on_this = state_manager::instance().cmd == MAIN_KEY ? true : false;
    if (!on_this) return;

    key = k; 

    switch (key) 
    {
      case 'h':
        prew_pwd();
        break;
    }
    werase(win_navigation);
    werase(win_history);
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
