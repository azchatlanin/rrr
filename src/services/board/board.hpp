#pragma once

#include <map>
#include <curses.h>

namespace rrr
{
  enum WIN_TYPE { LEFT, CENTER, RIGHT };
  inline std::map<WIN_TYPE, WINDOW*> w;
  inline int start_x = 0, start_y = 0, width, height;

  void init();
  void win_draw();

  inline int run()
  {
    init();
    win_draw();

    getch();
    endwin(); 
    return 0;
  }
  
  inline void init()
  {
    initscr();			
    cbreak();			
    keypad(stdscr, TRUE);		
    getmaxyx(stdscr, height, width);
  }

  inline void win_draw()
  {
    refresh();
    w.insert({ WIN_TYPE::LEFT, newwin(height, width / 3, start_y, start_x) });
    box(w[WIN_TYPE::LEFT], 0 , 0);		
    wrefresh(w[WIN_TYPE::LEFT]);	

    refresh();
    w.insert({ WIN_TYPE::CENTER, newwin(height, width / 3, start_y, start_x + width / 3) });
    box(w[WIN_TYPE::CENTER], 0 , 0);		
    wrefresh(w[WIN_TYPE::CENTER]);	

    refresh();
    w.insert({ WIN_TYPE::RIGHT, newwin(height, width / 3, start_y, start_x + 2 * width / 3) });
    box(w[WIN_TYPE::RIGHT], 0 , 0);		
    wrefresh(w[WIN_TYPE::RIGHT]);	
  }
}
