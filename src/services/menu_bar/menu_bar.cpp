#include "menu_bar.hpp"

namespace rrr
{
  std::shared_ptr<menu_bar> menu_bar::create()
  {
    static std::shared_ptr<menu_bar> ib = std::make_shared<menu_bar>();
    return ib;
  }

  menu_bar::menu_bar()
  {
    fill_menu();
    create_win();
  }

  void menu_bar::create_win()
  {
    //auto lr = layer::instance().get();

    // [[maybe_unused]] int max_y, max_x;
    // getmaxyx(lr->win, max_y, max_x);
    // getbegyx(lr->win, start_y, start_x);
    //
    // height = 3;
    // width = max_x;

    // win = newwin(height, width, start_y, start_x);
    // box(win, 0, 0);

    // mvaddstr(0, 3, "test");

    // keypad(win, true);
    // wrefresh(win);
  }

  void menu_bar::fill_menu()
  {
    m_items fm {
      { " New ", 1 }, 
      { " Edit ", 1 }, 
      { " Delete ", 1 }, 
      { " Select ", 1 }, 
      { " Copy ", 1 }, 
      { " Paste ", 1 }, 
      { " Quit ", 1 } 
    }; 

    m_items vm {
      { " Info ", 1 }
    }; 
    main_menu.emplace_back(std::make_pair( menu_item{" File ", 1 }, fm ));
    main_menu.emplace_back(std::make_pair( menu_item{" View ", 1 }, vm ));
  }

  void menu_bar::draw()
  {
    int pos = 3;
    for(auto& [key, val] : main_menu)
    {
      mvaddstr(0, pos, key.title.c_str());
      draw_submenu(val, pos);
      pos += key.title.length();
    }
  }

  void menu_bar::trigger(int key)
  {
    cmd = key;
  }

  void menu_bar::commit(event e)
  {}

  void menu_bar::rebuild()
  {
    refresh();
  }

  void menu_bar::draw_submenu(m_items items, int start_position)
  {
    int pos = 1;
    for(auto& item : items)
    {
      mvaddstr(pos, start_position, item.title.c_str());
      ++pos;
    }
  }
}
