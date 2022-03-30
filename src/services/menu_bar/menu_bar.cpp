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
    main_menu.emplace_back(" File ", "F");
    main_menu.emplace_back(" Info ", "I");
  }

  void menu_bar::draw()
  {
    int pos = 3;
    for(auto& menu_item : main_menu)
    {
      mvaddstr(0, pos, menu_item.first.c_str());
      pos += menu_item.first.length();
    }
    
    // layer::instance().get()->rebuild();
  }

  void menu_bar::trigger(int key)
  {}

  void menu_bar::commit(event e)
  {}

  void menu_bar::rebuild()
  {
    refresh();
  }
}
