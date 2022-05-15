#include "file.hpp"

#include "services/managers/state_manager/state_manager.hpp"

// hack
#include "logger/logger.hpp"
#include "utils/utils.hpp"

namespace rrr
{
  dir::dir(bool d) : is_dir { d } {}
  dir::dir(dir&& d) : is_dir { std::move(d.is_dir) } {}
  dir::dir(const dir& d) : is_dir { d.is_dir } {}

  dir& dir::operator=(const dir& d) 
  { 
    if (this == &d)
      return *this;
    is_dir = d.is_dir; 
    return *this;
  };

  bool dir::operator()() const 
  {
    return is_dir; 
  }

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

  bool file::operator==(const file& f) const
  { 
    if (this->path ==  f.path && this->in_buffer == f.in_buffer && this->is_directory() == f.is_directory())
      return true;
    return false;
  };

  std::ostream& operator<<(std::ostream& os, const file& f)
  {
    return os << f.path << std::endl;
  }

  void file::draw(bool is_selected, int pos_x, std::shared_ptr<WINDOW> win)
  {
    // attributes on
    if (directory())
      wattron(win.get(), COLOR_PAIR(1) | (is_selected ? A_BOLD : 0));
    else if (std::filesystem::is_symlink(path))
      wattron(win.get(), COLOR_PAIR(4) | (is_selected ? A_BOLD : 0));
    // else if (hack::utils::exec("test -x " + path.string() + " && echo true || echo false") == "true\n")
    //   wattron(win.get(), COLOR_PAIR(5) | A_BOLD);
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
    wattroff(win.get(), COLOR_PAIR(4) | (is_selected ? A_BOLD : 0));
    wattroff(win.get(), COLOR_PAIR(5) | A_BOLD);
    wattroff(win.get(), (is_selected ? A_BOLD : 0));
  }
}
