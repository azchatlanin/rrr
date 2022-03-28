#include "layer.hpp"

namespace rrr
{
  layer::layer()
  {
    init();
    create_win();
  };

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
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_GREEN);

    getmaxyx(stdscr, height, width);
    refresh();
  }
  
  void layer::create_win()
  {
    win = newwin(height, width, start_y, start_x);
    box(win, 0 , 0);	
    wrefresh(win);
  }

  void layer::draw()
  {
    for(auto& b : boards) b->draw();
  }

  void layer::rebuild()
  {
    refresh();
  }

  void layer::trigger(int key)
  {}

  void layer::add(std::shared_ptr<board> b)
  {
    boards.emplace_back(b);
  }
}
