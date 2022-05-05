#include "services/ncurses/style.hpp"
#include "services/ncurses/system.hpp"

#include "services/managers/manager/manager.hpp"
#include "services/ui/browser/browser.hpp"
#include "services/ui/info_bar/info_bar.hpp"
#include "services/ui/system_bar/system_bar.hpp"
#include "services/ui/command_line/command_line.hpp"

int main(int argc, char **argv)
{
  nc::init();
  nc::init_style();

  auto browser = rrr::board::make<rrr::browser>();
  auto info_bar = rrr::board::make<rrr::info_bar>();
  auto system_bar = rrr::board::make<rrr::system_bar>();
  auto command_line = rrr::board::make<rrr::command_line>();

  rrr::manager manager { browser, info_bar, system_bar, command_line };
  manager.draw();
  
  while(int key = getch())
  {
    manager.trigger(key);
    manager.draw();
    nc::refresh();
  }

  nc::end();
}
