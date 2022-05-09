#include "file.hpp"

#include "services/managers/state_manager/state_manager.hpp"

#include "logger/logger.hpp"

namespace rrr
{
  file::file(std::filesystem::path path_, bool is_dir) : path { path_ }, directory { is_dir } {}

  file::file(file&& f) : path { std::move(f.path) }, directory { std::move(f.directory) } {}

  file::file(const file& f) : path { f.path }, directory { f.directory } {}

  file& file::operator=(const file& other)
  {
    if (this == &other)
      return *this;
    
    path = other.path;
    directory = other.directory;

    return *this;
  }

  bool file::operator<(const file& other)
  {
    // используем тут дял сравнеия именно .compare т.к. это помогает делать верную сортировку
    // т.к. compare помогает сравнить имеено порядок
    return path.string().compare(other.path.string()) < 0;
  }

  void file::draw(bool is_selected, int pos_x, std::shared_ptr<WINDOW> win)
  {
    // attributes on
    if (directory())
      wattron(win.get(), COLOR_PAIR(1) | (is_selected ? A_BOLD : 0));
    else 
      wattron(win.get(), (is_selected  ? A_BOLD : 0));

    if (in_buffer)
      wattron(win.get(), COLOR_PAIR(2) | (is_selected ? A_BOLD : 0));

    // draw
    if (is_selected) mvwaddch(win.get(), pos_x + 1, 2, ACS_RARROW);
    mvwaddstr(win.get(), pos_x + 1, in_buffer ? 5 : 4, path.filename().string().c_str());

    // attributes off
    wattroff(win.get(), COLOR_PAIR(1) | (is_selected ? A_BOLD : 0));
    wattroff(win.get(), COLOR_PAIR(2) | (is_selected ? A_BOLD : 0));
    wattroff(win.get(), (is_selected ? A_BOLD : 0));
  }
}
