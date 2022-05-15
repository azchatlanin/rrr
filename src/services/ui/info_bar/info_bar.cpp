#include "info_bar.hpp"
#include <algorithm>
#include <filesystem>

namespace rrr
{

  info_bar::info_bar()
  {
    MAIN_KEYS = { 'I' };
    title = " info ";

    auto max_x = state_manager::instance().max_x;
    auto max_y = state_manager::instance().max_y;

    win = newwin(9, max_x / 2, max_y - 12, 0);
    box(win, 0, 0);
    set_title();

    pwd = state_manager::instance().PWD / buffer::state[state_manager::instance().PWD];

    wrefresh(win);
  }

  void info_bar::draw()
  {
    for (int i = 1; i < 7; ++i)
    {
      wmove(win, i, 1);
      clear();
    }

    //wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 1, 1, (" path: " + pwd.string() + file_size()).c_str());
    //wattroff(win, COLOR_PAIR(1) | A_BOLD);

    mvwaddstr(win, 3, 1, (" disk capacity:  " + disk_size(space_info.capacity)).c_str());
    mvwaddstr(win, 4, 1, (" disk free:      " + disk_size(space_info.free)).c_str());
    mvwaddstr(win, 5, 1, (" disk available: " + disk_size(space_info.available)).c_str());

    wrefresh(win);
  }

  std::string info_bar::file_size()
  {
    if (!std::filesystem::exists(pwd) || std::filesystem::is_directory(pwd)) return "";

    auto size = std::filesystem::file_size(pwd);
    return " (" + 
      (size > 1'000 ? std::to_string(size / 1'000) + "." + std::to_string(size%1'000) : std::to_string(size))
      + " kb)";
  }

  std::string info_bar::disk_size(std::intmax_t size)
  {
    return " " + 
      (size > 1'000'000'000 ? std::to_string(size / 1'000'000'000) + "." + std::to_string(size%1'000'000'000/1'000'000) : std::to_string(size))
      + " Gb";
  }

  void info_bar::set_title()
  {
    wattron(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 3, title.substr(0,2).c_str());
    wattroff(win, COLOR_PAIR(1) | A_BOLD);
    mvwaddstr(win, 0, 5, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void info_bar::trigger(int key)
  {
    if (!on_this()) return;
  }

  void info_bar::execute(event e, std::any data)
  {
    switch (e)
    {
      case CHANGE_PWD:
        pwd = std::any_cast<std::filesystem::path>(data);
        get_space_info();
        break;
      default:
        break;
    }
  }

  void info_bar::get_space_info()
  {
    if (!std::filesystem::exists(pwd) || !std::filesystem::is_directory(pwd)) return;
    space_info = std::filesystem::space(pwd);
  }

  void info_bar::clear()
  {
    wclrtoeol(win);
    box(win, 0, 0);
    set_title();
  }
}
