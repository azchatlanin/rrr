#include "services/layer/layer.hpp"
#include "services/info_bar/info_bar.hpp"

int main(int argc, char **argv)
{
  auto layer = rrr::layer::instance().get();

  //auto menu_bar = rrr::menu_bar::create();
  auto info_bar = rrr::info_bar::create();

  //layer.add(menu_bar);
  layer->add(info_bar);
  
  layer->draw();
  
  while(int key = getch())
  {
    layer->trigger(key);
    layer->draw();
  }
  
  endwin();
}
