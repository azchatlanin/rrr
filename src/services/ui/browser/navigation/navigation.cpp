#include "navigation.hpp"

#include "logger/logger.hpp"

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
    
    std::vector<file>::iterator it;
    auto futer = state_manager::instance().max_y - 15;
    int begin = cursor_pos > futer - 1 ? cursor_pos - futer + 1: 0;
    auto end = current_files.begin() + begin + futer > current_files.end() ? current_files.end() : current_files.begin() + begin + futer;
    int i;
    int pos = 0;
    for(it = current_files.begin() + begin, i = begin; it != end; ++i, ++it, ++pos)
    { 
      bool select = cursor_pos == i;
      it->draw(select, pos, win);
    }

    if (current_files.empty())
      draw_content();

    wrefresh(win.get());
  }

  void navigation::set_cursor_pos(std::filesystem::path p)
  {
    for (auto& f : current_files)
    {
      auto i = &f - current_files.data();
      if (f.path == p)
        cursor_pos = i;
    }
  }

  void navigation::buffer_update()
  {
    for(auto& f : current_files)
    {
      auto i = &f - current_files.data();
      bool select = cursor_pos == i;
      if (select)
        buffer::state[state_manager::instance().PWD] = f.path;
    }
  }

  std::string navigation::get_content()
  {
    return content;
  }

  void navigation::draw_content()
  {
    wattron(win.get(), COLOR_PAIR(3) | A_BOLD);
    mvwaddstr(win.get(), 1, 0, content.c_str());
    wattroff(win.get(), COLOR_PAIR(3) | A_BOLD);
  }

  int navigation::get_cursor_pos()
  {
    return cursor_pos;
  }

  file_utils::files navigation::get_current_files()
  {
    return current_files;
  }

  // заполняет массив с файлами из текущей директории
  void navigation::fill()
  {
    auto pwd = state_manager::instance().PWD;

    if (std::filesystem::is_directory(pwd))
      current_files = file_utils::fill(pwd);
  }

  // чистим буфер при выборе пробелом
  // и делаем сам выбор
  void navigation::select()
  {
    auto&& bf = state_manager::instance().buffer_path;
    auto pwd = state_manager::instance().PWD;
    bool exist = false;

    if (std::find(bf.begin(), bf.end(),  pwd / buffer::state[pwd]) != bf.end())
      exist = true;

    if (!exist) bf.push_back(pwd / buffer::state[pwd]);

    for (auto& f : current_files)
    {
      if (std::find(bf.begin(), bf.end(), f.path) != std::end(bf))
      {
        auto i = &f - current_files.data();
        if (cursor_pos == i) f.in_buffer = !f.in_buffer;
      }
    }

    if (exist)
      bf.erase(std::remove_if(bf.begin(), bf.end(), [&](const std::filesystem::path& p){ return p == pwd / buffer::state[pwd]; }));
  }

  void navigation::set_cursor_pos(int i)
  {
    cursor_pos += i;
    cursor_check();
  }

  void navigation::cursor_up()
  {
    --cursor_pos;
    cursor_check();
  }
  
  void navigation::cursor_down()
  {
    ++cursor_pos;
    cursor_check();
  }

  void navigation::cursor_check()
  {
    if (cursor_pos >= static_cast<int>(current_files.size())) cursor_pos = current_files.size() - 1;
    if (cursor_pos < 0) cursor_pos = 0;
  }

  void navigation::set_cursor_pos()
  {
    if (current_files.empty())
    {
      cursor_pos = 0;
      return;
    }

    auto bf_state = buffer::state[state_manager::instance().PWD];

    auto find_pred = [&](file f) -> bool { return f.path == bf_state; };
    auto it = std::find_if(current_files.begin(), current_files.end(), find_pred);
    cursor_pos = it == std::end(current_files) ? 0 : std::distance(current_files.begin(), it);
  }
}
