#include "navigation.hpp"

#include "utils/utils.hpp"

namespace rrr
{

  navigation::navigation(WINDOW* parent_win, int h, int w, int pos_y, int pos_x)
  {
    win.reset(derwin(parent_win, h, w, pos_y, pos_x));
    current_files = file_utils::fill(state_manager::instance().PWD);
    buffer_update();
    set_cursor_pos();
  };
  
  void navigation::draw()
  {
    if (!std::filesystem::is_directory(state_manager::instance().PWD))
      return;

    dirs_draw();
    wrefresh(win.get());
  }

  void navigation::set_cursor_pos(int i)
  {
    select_pos += i;

    if (select_pos <= 0) select_pos = 0;
    if (select_pos >= static_cast<int>(current_files.size())) select_pos = current_files.size() - 1;
  }

  void navigation::buffer_update()
  {
    for(auto& f : current_files)
    {
      auto i = &f - current_files.data();
      bool select = select_pos == i;
      if (select)
        buffer::state[state_manager::instance().PWD] = f.path;
    }
  }

  void navigation::dirs_draw()
  {
    for(auto& f : current_files)
    {
      auto i = &f - current_files.data();
      bool select = select_pos == i;
      f.draw(select, i, win);
    }
  }

  // @anotation
  // заполняет массив с файлами из текущей директории
  void navigation::fill()
  {
    if (!std::filesystem::is_directory(state_manager::instance().PWD))
      return;

    current_files = file_utils::fill(state_manager::instance().PWD);
  }

  void navigation::set_cursor_pos()
  {
    if (current_files.empty()) return;

    file_name = buffer::state[state_manager::instance().PWD].filename();

    auto find_pred = [&](file f) -> bool {
      return f.path.filename() == file_name;
    };

    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    select_pos = it == std::end(current_files) ? 0 : std::distance(current_files.begin(), it);
  }
}