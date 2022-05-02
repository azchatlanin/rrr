#include "browser.hpp"

#include "utils/utils.hpp"

namespace rrr
{
  browser::browser() : board { 'F' }
  {
    title = " File browser ";    

    state_manager::instance().PWD = hack::utils::exec("pwd");
    state_manager::instance().PWD.erase(std::remove(state_manager::instance().PWD.begin(), state_manager::instance().PWD.end(), '\n'), state_manager::instance().PWD.end());
    fill(current_files, state_manager::instance().PWD);

    getmaxyx(stdscr, ft.height, ft.width);
    state_manager::instance().max_y = ft.height;
    state_manager::instance().max_x = ft.width;

    ft.height -= ft.height / 7;

    win = newwin(ft.height, ft.width, ft.start_y, ft.start_x);
    box(win, 0 , 0);	
    set_title();

    win_history = std::make_shared<history>(win, ft.height - 2, ft.width / 3, 1, 1);
    win_navigation = derwin(win, ft.height - 2, ft.width / 3 + 1, 1, ft.width / 3);
    win_preview = std::make_shared<decorator>(win, ft.height - 2, ft.width / 3 - 1, 1, ft.width * 2 / 3);

    wrefresh(win);
    wrefresh(win_history->win.get());
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
    auto pos = state_manager::instance().PWD.find_last_of("/");
    auto file_name = state_manager::instance().PWD.substr(pos + 1);

    state_manager::instance().PWD = pos ? state_manager::instance().PWD.substr(0, pos) : "/";
    fill(current_files, state_manager::instance().PWD);
    BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD); 

    select_pos = 0;

    // fill pos in no state
    for (auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      if (file_name.compare(f.name) == 0)
        select_pos = i;
    }

    // fill pos if exist state
    for (auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      if (state[state_manager::instance().PWD].compare(f.name) == 0)
        select_pos = i;
    }
  }

  void browser::next_pwd()
  {
    if (!std::filesystem::is_directory(state_manager::instance().PWD + (state_manager::instance().PWD.compare("/") == 0 
      ? std::string(current_files.at(select_pos).name) 
      : "/" + std::string(current_files.at(select_pos).name)))) return;

    state_manager::instance().PWD += state_manager::instance().PWD.compare("/") == 0 
      ? std::string(current_files.at(select_pos).name) 
      : "/" + std::string(current_files.at(select_pos).name);

    fill(current_files, state_manager::instance().PWD);
    select_pos = 0;

    for (auto& f : current_files)
    {
      auto i = &f - current_files.data();
      if (state[state_manager::instance().PWD].compare(f.name) == 0)
        select_pos = i;
    }
  }

  void browser::draw()
  {
    for(auto& f : current_files)
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
      {
        state[state_manager::instance().PWD] = f.name;
        BOARD->execute(event::CHANGE_PWD, state_manager::instance().PWD + "/" + f.name); 
      }

    }

    if (std::filesystem::is_directory(state_manager::instance().PWD))
    {
      win_history->set_pwd();
      win_history->draw();
    }
    
    if (std::filesystem::is_directory(state_manager::instance().PWD + "/" + state[state_manager::instance().PWD]))
    {
      win_preview->set_pwd(state_manager::instance().PWD + "/" + state[state_manager::instance().PWD]);
      win_preview->set_pos(state[state_manager::instance().PWD + "/" + state[state_manager::instance().PWD]]);
    }
    else
    {
      // win_preview->set_pwd(PWD);
      // win_preview->set_pos(state[PWD]);
    }

    win_preview->draw();

    wrefresh(win_navigation);
    wrefresh(win_preview->win);
  }

  void browser::up()
  {
    --select_pos;
  }

  void browser::down()
  {
    ++select_pos;
  }

  void browser::trigger(int k)
  {
    if (!on_this()) return;

    key = k; 
    switch (key) 
    {
      // selsect
      case 'h':
        prew_pwd();
        break;
      case 'l':
        next_pwd();
        break;
      case KEY_ENTER:
        next_pwd();
        break;
      case 10: // this is a key enter too
        next_pwd();
        break;
        
      // navigation
      case 'j':
        down();
        break;
      case KEY_DOWN:
        down();
        break;
      case 'k':
        up();
        break;
      case KEY_UP:
        up();
        break;
    }

    if (select_pos <= 0) select_pos = 0;
    if (select_pos >= static_cast<int>(current_files.size())) select_pos = current_files.size() - 1;

    werase(win_navigation);
    werase(win_history->win.get());
    werase(win_preview->win);
  }

  void browser::execute(event e, std::any) {}
}
