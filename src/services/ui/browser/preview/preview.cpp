#include "preview.hpp"

// hack 
#include "utils/utils.hpp"
#include "logger/logger.hpp"

namespace rrr
{

  preview::preview(WINDOW* parent_win, int h, int w, int pos_y, int pos_x)
  {
    win.reset(derwin(parent_win, h, w, pos_y, pos_x));
  };
  
  void preview::draw()
  {
    if (std::filesystem::is_directory(buffer::state[state_manager::instance().PWD]))
      draw_dirs();
    else 
      draw_content();

    wrefresh(win.get());
  }

  void preview::draw_dirs()
  {
    for(auto&& f : current_files)
    {
      auto i = &f - current_files.data();
      f.draw(cursor_pos == i, i, win);
    }

    if (current_files.empty())
      draw_content();
  }

  int preview::get_cursor_pos()
  {
    return cursor_pos;
  }

  file_utils::files preview::get_current_files()
  {
    return current_files;
  }

  void preview::draw_content()
  {
    wattron(win.get(), COLOR_PAIR(3) | A_BOLD);
    mvwaddstr(win.get(), 1, 0, content.c_str());
    wattroff(win.get(), COLOR_PAIR(3) | A_BOLD);
  }

  void preview::fill()
  {
    auto pwd = buffer::state[state_manager::instance().PWD];

    if (std::filesystem::is_directory(pwd))
    {
      current_files = file_utils::fill(pwd);
      set_cursor_pos();
    }
    else if (!pwd.empty() && std::filesystem::exists(pwd))
    {
      // делаем ограничение на размер файла, а то много читать бяда-печaль
      content = std::filesystem::file_size(pwd) < 1'000'000 ? hack::utils::exec("cat " + pwd.string()) : "this file size is very big";
      content = content.empty() ? "is empty" : content;
      cursor_pos = 0;
      current_files.clear();
    }
    else 
    {
      content = "is empty";
      cursor_pos = 0;
      current_files.clear();
    }
  }

  std::string preview::get_content()
  {
    return content;
  }

  // @anotation
  // устанавливает текущуюю позицию курсора относительно информации из буфера
  void preview::set_cursor_pos()
  {
    if (current_files.empty()) return;

    auto pwd = buffer::state[state_manager::instance().PWD];
    std::filesystem::path file_name;

    if (std::filesystem::is_directory(pwd))
      file_name = buffer::state[pwd].filename();

    auto find_pred = [&](file f) -> bool {
      return f.path.filename() == file_name;
    };

    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    cursor_pos = it == std::end(current_files) ? 0 : std::distance(current_files.begin(), it);
  }
}
