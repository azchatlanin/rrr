#include "services/managers/manager.hpp"
#include "services/ui/browser/browser.hpp"
#include "services/ui/info_bar/info_bar.hpp"
#include "services/ui/menu_bar/menu_bar.hpp"

void init_style()
{
  if (!has_colors()) throw "Don't set color";
  start_color();

  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
}

void init_nc()
{
  initscr();
  noecho();
  curs_set(0);
  cbreak();			
  keypad(stdscr, TRUE);
  refresh();
}

template<typename T>
using board = std::shared_ptr<T>;

int main(int argc, char **argv)
{
  init_nc();
  init_style();

  board<rrr::browser> browser = rrr::browser::create<rrr::browser>();
  board<rrr::menu_bar> menu_bar = rrr::menu_bar::create<rrr::menu_bar>();
  board<rrr::info_bar> info_bar = rrr::board::create<rrr::info_bar>();
  
  rrr::manager<rrr::board,
               rrr::board,
               rrr::board> manager { std::move(browser), std::move(menu_bar), std::move(info_bar) };

  manager.draw();
  
  while(int key = getch())
  {
    manager.trigger(key);
    manager.draw();
    refresh();
    usleep(1000);
  }
  
  endwin();
}
