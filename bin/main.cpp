#include "services/manager/manager.hpp"
#include "services/browser/browser.hpp"
#include "services/info_bar/info_bar.hpp"
#include "services/menu_bar/menu_bar.hpp"

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

int main(int argc, char **argv)
{
  init_nc();
  init_style();

  auto browser = rrr::browser::create();
  auto menu_bar = rrr::menu_bar::create();
  auto info_bar = rrr::info_bar::create();
  
  rrr::manager<rrr::board,
               rrr::board,
               rrr::board> manager { std::move(browser), std::move(menu_bar), std::move(info_bar) };

  manager.draw();
  
  while(int key = getch())
  {
    manager.trigger(key);
    manager.draw();
    usleep(1000);
  }
  
  endwin();
}
