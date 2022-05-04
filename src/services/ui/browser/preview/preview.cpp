#include "preview.hpp"

#include "utils/utils.hpp"

namespace rrr
{

  preview::preview(WINDOW* parent_win, int h, int w, int pos_y, int pos_x)
  {
    win.reset(derwin(parent_win, h, w, pos_y, pos_x));
  };
  
  void preview::draw()
  {
    if (std::filesystem::is_directory(pwd))
      dirs_draw();

    wrefresh(win.get());
  }

  void preview::dirs_draw()
  {
    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      f.draw(select_pos == i, i, win);
    }
  }

  void preview::fill()
  {
    pwd = state_manager::instance().PWD / buffer::state[state_manager::instance().PWD].filename();

    if (!std::filesystem::is_directory(pwd))
      return;

    current_files = file_utils::fill(pwd);
    set_cursor_pos();
  }

  // @anotation
  // устанавливает текущуюю позицию курсора относительно информации из буфера
  void preview::set_cursor_pos()
  {
    if (current_files.empty()) return;

    std::filesystem::path file_name;

    if (std::filesystem::is_directory(pwd))
      file_name = buffer::state[pwd].filename();

    auto find_pred = [&](file f) -> bool {
      return f.path.filename() == file_name;
    };

    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    select_pos = it == std::end(current_files) ? 0 : std::distance(current_files.begin(), it);
  }
}
