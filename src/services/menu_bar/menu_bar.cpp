#include "menu_bar.hpp"

#include "logger/logger.hpp"

namespace rrr
{
  menu::menu(std::string text, char trigger, m_menu items) 
    : text { text }, trigger { trigger }, items { items } 
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

  menu_bar::menu_bar(WINDOW* win) : win { win }
  {
    menus.emplace_back(menu { "File", 'F', config::f_menu });
    menus.emplace_back(menu { "Info", 'I', config::i_menu });
  }

  void menu_bar::init()
  {
    int pos = 0;
    for(auto& m : menus)
    {
      m.start_x = current_pos;
      current_pos += m.text.size() + 2;
      for (const auto& t : m.items)
        pos = pos < (t.first.size() + t.second.size() + 4) ? (t.first.size() + t.second.size() + 4) : pos;
    }

    int y_max, x_max, y_beg, x_beg;
    getmaxyx(win, y_max, x_max);
    getbegyx(win, y_beg, x_beg);

    menu_win = newwin(y_max - 2, pos, y_beg + 1, x_beg + 1);
    box(menu_win, 0, 0);

    keypad(menu_win, true);
    wrefresh(menu_win);
  }

  void menu_bar::draw()
  {
    for(auto& m : menus)
    {
      draw_menu(m, selected == m.trigger);
    }
    selected = -1;
  }

  void menu_bar::press(char c)
  {
    selected = c;
  }

  void menu_bar::draw_menu(menu& m, bool is_selected)
  {
    if (selected == m.trigger)
      wattron(win, A_STANDOUT);
    mvwprintw(win, 0, m.start_x, m.text.c_str());
    wattroff(win, A_STANDOUT);
    wrefresh(win);

    draw_menu_item(m);
    wrefresh(menu_win);

    int ch;
    while (is_selected && (ch = wgetch(menu_win)))
    {
      switch (ch)
      {
        case 'j':
          m.selected_next();
          break;
        case 'k':
          m.selected_prew();
          break;
        default:
          is_selected = false;
      }
      draw_menu_item(m);
    }

    werase(menu_win);
    wrefresh(menu_win);
    reset();
  }

  void menu_bar::draw_menu_item(const menu& m)
  {
    int x_max = getmaxx(menu_win);
    int index = 0;

    for (const auto& el : m.items)
    {
      mvwprintw(menu_win, index, 0, std::string(el.first + " (" + el.second + ")").data() );
      // el.second.compare(m.selected_item->second) ?
      //   mvwchgat(menu_win, index, 0, x_max, A_NORMAL, 1, NULL) :
      //   mvwchgat(menu_win, index, 0, x_max, A_STANDOUT, 0, NULL);
      hack::log()(index, el.first);
      index++;
    }
  }

  void menu_bar::reset()
  {
    for(auto m : menus)
    {
      mvwprintw(win, 0, m.start_x, m.text.c_str());
    }
    wrefresh(win);
  }
}
