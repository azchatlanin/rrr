#include "history.hpp"

#include "utils/utils.hpp"

namespace rrr
{

  history::history(WINDOW* parent_win, int h, int w, int pos_y, int pos_x)
  {
    win.reset(derwin(parent_win, h, w, pos_y, pos_x));
  };
  
  void history::draw()
  {
    is_last ? root_draw() : dirs_draw();
    wrefresh(win.get());
  }

  void history::root_draw()
  {
    wattron(win.get(), COLOR_PAIR(1) | A_BOLD);
    mvwaddch(win.get(), 1, 2, ACS_RARROW);
    mvwaddstr(win.get(), 1, 4, "/");
    wattroff(win.get(), COLOR_PAIR(1) | A_BOLD);
  }

  void history::dirs_draw()
  {
    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      f.draw(select_pos == i, i, win);
    }
  }

  void history::set_pwd()
  {
    auto pos = state_manager::instance().PWD.find_last_of("/");
    std::string pwd = pos ? state_manager::instance().PWD.substr(0, pos) : "/";
    std::string relative_pwd = std::filesystem::path(state_manager::instance().PWD).relative_path();

    if (relative_pwd.compare("") == 0)
    {
      pwd = "/";
      is_last = true;
      return;
    }
    else 
      is_last = false;

    fill(current_files, pwd);
    set_pos();
  }

  void history::set_pos()
  {
    std::string pwd_slice = state_manager::instance().PWD.substr(state_manager::instance().PWD.find_last_of("/") + 1);

    auto find_pred = [&](File f) -> bool { 
      return f.name.compare(pwd_slice) == 0 ? true : false;
    };

    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    select_pos = it != std::end(current_files) ? it - current_files.begin() : 0;
  }
}
