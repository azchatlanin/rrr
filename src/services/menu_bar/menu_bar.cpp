#include "menu_bar.hpp"

namespace rrr
{
  menu_bar::menu_bar()
  {
    fill_menu();
  }

  void menu_bar::create_win()
  {
    auto max_x = state::instance().get()->max_x;
    auto max_y = state::instance().get()->max_y;

    height = max_y / 12;
    width = max_x / 22;
    start_y = 1;
    win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    keypad(win, true);
    wrefresh(win);
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

    main_menu.emplace_back(std::make_pair( menu_item{" File ", 70 }, fm ));
    main_menu.emplace_back(std::make_pair( menu_item{" View ", 86 }, vm ));
  }

  void menu_bar::draw()
  {
    wrefresh(win);
    int x = 3;
    for (auto& [key, val] : main_menu)
    {
      set_menu_title(0, x, key.title, 1);
      if (cmd == key.cmd)
      {
        rebuild();
        start_x = x - 1;
        set_menu_title(0, x, key.title, 2);
        create_win();
        draw_submenu(val, x);
      }
      x += key.title.length();
    }
    wrefresh(win);
  }

  void menu_bar::set_menu_title(int y, int x, std::string title, int color)
  {
    attron(COLOR_PAIR(color) | A_BOLD);
    mvaddstr(y, x, title.substr(0,2).c_str());
    attroff(COLOR_PAIR(color) | A_BOLD);
    mvaddstr(y, x + 2, title.substr(2, title.at(title.length()-1)).c_str());
  }

  void menu_bar::trigger(int key)
  {
    cmd = key;
  }

  void menu_bar::commit(event e)
  {}

  void menu_bar::rebuild()
  {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
  }

  void menu_bar::draw_submenu(m_items items, int x)
  {
    int y = 2;
    for (auto& item : items)
    {
      set_menu_title(y, x, item.title, 1);
      ++y;
    }
  }
}
