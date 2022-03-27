#include "layer.hpp"

#include "menu_bar/menu_bar.hpp"

namespace rrr
{
  layer::layer()
  {
    init();
    create_win();
  };

  layer::~layer()
  {
    wborder(layer_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(layer_win);
    delwin(layer_win);
  }

  std::shared_ptr<layer> layer::instance()
  {
    static std::shared_ptr<layer> br(new layer);
    return br;
  }

  void layer::init()
  {
    initscr();
    noecho();
    curs_set(0);
    cbreak();			
    keypad(stdscr, TRUE);
    
    if (!has_colors()) throw "Don't set color";
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);

    getmaxyx(stdscr, height, width);
    refresh();
  }
  
  void layer::create_win()
  {
    layer_win = newwin(height, width, start_y, start_x);
    box(layer_win, 0 , 0);	
    wrefresh(layer_win);
  }

  void layer::draw()
  {

  }

  void layer::trigger(int key)
  {}

  void layer::add(std::shared_ptr<board> b)
  {
    boards.emplace_back(b);
  }
}
