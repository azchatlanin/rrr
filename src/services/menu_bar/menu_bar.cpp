#include "menu_bar.hpp"

namespace rrr
{
  void menu_bar::draw_menu_item(menu m)
  {
    int y_max, x_max;
    getmaxyx(menu_win, y_max, x_max);
    for (int i = 0; i < m.num_items; i++)
    {
      mvwprintw(menu_win, i, 0, m.items[i].c_str());
      if (m.selected_item == i)
      {
        mvwchgat(menu_win, i, 0, x_max, A_NORMAL, 1, NULL);
      }
      else 
      {
        mvwchgat(menu_win, i, 0, x_max, A_STANDOUT, 0, NULL);
      }

    }
  }

  void menu_bar::draw_menu(menu m, bool is_selected)
  {
    if (selected == m.trigger)
      wattron(win, A_STANDOUT);
    mvwprintw(win, 0, m.start_x, m.text.c_str());
    wattroff(win, A_STANDOUT);
    wrefresh(win);

    int ch;
    draw_menu_item(m);
    wrefresh(menu_win);
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

  void menu_bar::draw()
  {
    for(auto m : menus)
    {
      draw_menu(m, selected == m.trigger);
    }
    selected = -1;
  }

  void menu_bar::reset()
  {
    for(auto m : menus)
    {
      mvwprintw(win, 0, m.start_x, m.text.c_str());
    }
    wrefresh(win);
  }

  void menu_bar::init()
  {
    for(auto& m : menus)
    {
      m.start_x = current_pos;
      current_pos += m.text.size() + 2;
    }

    int y_max, x_max, y_beg, x_beg;
    getmaxyx(win, y_max, x_max);
    getbegyx(win, y_beg, x_beg);
    menu_win = newwin(y_max - 2, x_max - 2, y_beg + 1, x_beg + 1);
    keypad(menu_win, true);
    wrefresh(menu_win);
  }

  void menu_bar::press(char c)
  {
    selected = c;
  }
}
