#include "browser.hpp"

#include <curses.h>
#include <iterator>

#include "utils/utils.hpp"

namespace rrr
{

  browser::browser()
  {
    title = " File browser ";    

    PWD = hack::utils::exec("pwd");
    PWD.erase(std::remove(PWD.begin(), PWD.end(), '\n'), PWD.end());
    fill(current_files, PWD);

    getmaxyx(stdscr, ft.height, ft.width);
    state_manager::instance().max_y = ft.height;
    state_manager::instance().max_x = ft.width;

    ft.width -= ft.width / 7;

    win = newwin(ft.height, ft.width, ft.start_y, ft.start_x);
    box(win, 0 , 0);	
    set_title();

    win_history = std::make_shared<decorator>(win, ft.height - 2, ft.width / 3, 1, 1);
    win_navigation = derwin(win, ft.height - 2, ft.width / 3 + 1, 1, ft.width / 3);
    win_preview = std::make_shared<decorator>(win, ft.height - 2, ft.width / 3 - 1, 1, ft.width * 2 / 3);

    wrefresh(win);
    wrefresh(win_history->win);
    wrefresh(win_navigation);
    wrefresh(win_preview->win);
  };
  
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
    fill(current_files, PWD);
  }

  void browser::next_pwd()
  {
    PWD += "/" + std::string(current_files.at(select_pos).name);
    fill(current_files, PWD);
  }

  void browser::draw()
  {
    auto pos = PWD.find_last_of("/");
    auto PWD_PREW = pos ? PWD.substr(0, pos) : "/";

    win_history->set_pwd(PWD_PREW);
    win_history->set_pos(PWD);
    win_history->draw();
    
    set_cursor_position();

    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();

      if (f.type == config::type::FILE_TYPE::DIR)
      {
        wattron(win_navigation, COLOR_PAIR(1) | (select_pos == i ? A_BOLD : 0));
        select_pos == i ? mvwaddch(win_navigation, i + 1, 2, ACS_RARROW) : 0;
      }
      else
      {
        wattron(win_navigation, (select_pos == i ? A_BOLD : 0));
        select_pos == i ? mvwaddch(win_navigation, i + 1, 2, ACS_RARROW) : 0;
      }
      mvwaddstr(win_navigation, i + 1, 4, f.name.c_str());
      wattroff(win_navigation, COLOR_PAIR(1) | (select_pos == i ? A_BOLD : 0));
      wattroff(win_navigation, (select_pos == i ? A_BOLD : 0));

      if (select_pos == i)
        state[PWD] = f.name;
    }

    win_preview->set_pwd(PWD + "/" + state[PWD]);
    win_preview->set_pos(state[PWD + "/" + state[PWD]]);
    win_preview->draw();

    wrefresh(win_navigation);
    wrefresh(win_preview->win);
  }

  void browser::set_cursor_position()
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
    if (select_pos >= static_cast<int>(current_files.size())) select_pos = current_files.size() - 1;
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
      case 'l':
        next_pwd();
        break;
      case KEY_ENTER:
        next_pwd();
        break;
      case 10: // key enter too
        next_pwd();
        break;
    }
    werase(win_navigation);
    werase(win_history->win);
    werase(win_preview->win);
  }
}
