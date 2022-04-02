#include "menu_bar.hpp"

#include "utils/config.hpp"

namespace rrr
{
  menu_bar::menu_bar()
  {
    fill_menu();
  }

  void menu_bar::create_win()
  {
    auto max_x = state_manager::instance().get()->max_x;
    auto max_y = state_manager::instance().get()->max_y;

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
      { " New ", config::key::TOP_MENU::FILE::NEW }, 
      { " Edit ", config::key::TOP_MENU::FILE::EDIT }, 
      { " Delete ", config::key::TOP_MENU::FILE::DELETE }, 
      { " Select ", config::key::TOP_MENU::FILE::SELECT }, 
      { " Copy ", config::key::TOP_MENU::FILE::COPY }, 
      { " Paste ", config::key::TOP_MENU::FILE::PASTE }, 
      { " Quit ", config::key::TOP_MENU::FILE::QUITE } 
    }; 

    m_items vm {
      { " Info ", config::key::TOP_MENU::VIEW::INFO },
      { " Logs ", config::key::TOP_MENU::VIEW::LOGS },
      { " Monitor ", config::key::TOP_MENU::VIEW::MONITOR },
      { " Script ", config::key::TOP_MENU::VIEW::SCRIPT }
    }; 

    main_menu.emplace_back(std::make_pair( menu_item{" File ", config::key::TOP_MENU::FILE::FILE }, fm ));
    main_menu.emplace_back(std::make_pair( menu_item{" View ", config::key::TOP_MENU::VIEW::VIEW }, vm ));
  }

  void menu_bar::draw()
  {
    wrefresh(win);
    on_this = false;
    int x = 3;
    for (auto& [key, val] : main_menu)
    {
      set_menu_title(0, x, key.title, 1);
      if (state_manager::instance().get()->main_state.compare(key.cmd) == 0)
      {
        on_this = true;
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

  void menu_bar::draw_submenu(m_items items, int x)
  {
    int y = 2;
    for (auto& item : items)
    {
      if (current_select_pos < 0) current_select_pos = 0;
      if (current_select_pos >= (int)items.size()) current_select_pos = items.size() - 1;

      if((current_select_pos + 2) == y)
        mvaddstr(y, x, config::ICON::MENU_SELECT.c_str());
      set_menu_title(y, x + 1, item.title, 1);
      ++y;
    }
    BOARD->execute(this, event::rebuild_browser);
    rebuild();
  }

  void menu_bar::trigger()
  {
    if (state_manager::instance().get()->cmd.compare(config::key::TOP_MENU::FILE::FILE) == 0 || 
        state_manager::instance().get()->cmd.compare(config::key::TOP_MENU::VIEW::VIEW) == 0)
      current_select_pos = 0;

    if (on_this && state_manager::instance().get()->cmd.compare(config::key::MOVE::MOVE_DOWN) == 0) 
      ++current_select_pos;
    if (on_this && state_manager::instance().get()->cmd.compare(config::key::MOVE::MOVE_UP) == 0) 
      --current_select_pos;
  }

  void menu_bar::commit(event e)
  {}
}
