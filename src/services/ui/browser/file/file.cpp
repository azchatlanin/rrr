#include "file.hpp"

namespace rrr
{
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
    return path.string().compare(other.path.string()) < 0;
  }

  void file::draw(bool is_selected, int pos_x, std::shared_ptr<WINDOW> win)
  {
    // attributes on
    if (directory())
      wattron(win.get(), COLOR_PAIR(1) | (is_selected ? A_BOLD : 0));
    else 
      wattron(win.get(), (is_selected  ? A_BOLD : 0));

    // draw
    if (is_selected) mvwaddch(win.get(), pos_x + 1, 2, ACS_RARROW);
    mvwaddstr(win.get(), pos_x + 1, 4, path.filename().string().c_str());

    // attributes off
    wattroff(win.get(), COLOR_PAIR(1) | (is_selected ? A_BOLD : 0));
    wattroff(win.get(), (is_selected ? A_BOLD : 0));
  }
}
