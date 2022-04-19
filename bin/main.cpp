#include "services/managers/manager.hpp"
#include "services/ui/browser/browser.hpp"
#include "services/ui/info_bar/info_bar.hpp"

void init_style()
{
  if (!has_colors()) throw "Don't set color";
  start_color();

  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  use_default_colors();
}

void init_nc()
{
  initscr();
  noecho();
  curs_set(0);
  cbreak();			
  keypad(stdscr, TRUE);
  ESCDELAY=0;
  refresh();
}

int main(int argc, char **argv)
{
  init_nc();
  init_style();
  
  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();

  // начать новых досок и методов board

  rrr::manager manager { browser, info_bar };
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
