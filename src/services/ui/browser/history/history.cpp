#include "history.hpp"

namespace rrr
{

  history::history(WINDOW* parent_win, int h, int w, int pos_y, int pos_x)
  {
    win.reset(derwin(parent_win, h, w, pos_y, pos_x));
  };
  
  void history::draw()
  {
    if (!std::filesystem::is_directory(state_manager::instance().PWD))
      return;
      
    is_last ? root_draw() : dirs_draw();
    wrefresh(win.get());
  }

  int history::get_cursor_pos()
  {
    return cursor_pos;
  }

  file_utils::files history::get_current_files()
  {
    return current_files;
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
      f.draw(cursor_pos == i, i, win);
    }
  }

  // HERE
  // сохранять историю пути если мы переименовали файл
  // это сложно, но прикольно. нужно редактировать сами ключи.
  // необязательная фишка, но интересная
  void history::fill()
  {
    if (!std::filesystem::is_directory(state_manager::instance().PWD))
      return;

    if (state_manager::instance().PWD == state_manager::instance().PWD.root_path())
      is_last = true;
    else
      is_last = false;

    std::filesystem::path parent_path = state_manager::instance().PWD.parent_path();
    current_files = file_utils::fill(parent_path);
    set_cursor_pos();
  }

  void history::set_cursor_pos()
  {
    if (current_files.empty()) return;

    std::filesystem::path file_name = state_manager::instance().PWD.filename();

    auto find_pred = [&](file f) -> bool {
      return f.path.filename() == file_name;
    };

    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    cursor_pos = std::distance(current_files.begin(), it);
  }
}
