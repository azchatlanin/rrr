#pragma once

#include <map>
#include <curses.h>
#include <menu.h>

#include <panel.h>
#include <string.h>
#include "tools/src/logger/logger.hpp"

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

namespace rrr
{
  inline int start_x, start_y, width, height;

  class board
  {
    public:
      board() = default;
      ~board() = default;

    public:
      void init();

    private:
      WINDOW* win;
  };
  




  //----------------
  enum WIN_TYPE { LEFT, CENTER, RIGHT };
  inline std::map<WIN_TYPE, WINDOW*> w;
 
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
