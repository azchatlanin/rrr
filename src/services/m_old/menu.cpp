#include "menu.hpp"

namespace rrr
{
  menu::menu(std::string text_, char trigger_, m_menu items_) : text { text_ }, trigger { trigger_ }, items { items_ } 
  {
    selected_item = items.begin();
  }

  void menu::selected_next()
  {
    selected_item++;
    if (selected_item == items.end()) selected_item = items.begin();
  }

  void menu::selected_prew()
  {
    if (selected_item == items.begin()) selected_item = items.end();
    if (selected_item != items.begin()) selected_item--;
  }
}
