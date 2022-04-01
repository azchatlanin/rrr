#pragma once

#include <curses.h>
#include <memory>
#include <vector>

#include "services/manager/manager.hpp"

namespace rrr
{
  class browser : public board
  {
    public:
      browser();

    public:
      void draw() override;
      void rebuild() override;
      void trigger(int) override;
      void commit(event) override;

    private: 
      void create_win() override;
  };




  //----------------
 //  enum WIN_TYPE { LEFT, CENTER, RIGHT };
 //  inline std::map<WIN_TYPE, WINDOW*> w;
 // 
 //  inline void win_draw()
 //  {
 //    refresh();
 //    w.insert({ WIN_TYPE::LEFT, newwin(height, width / 3, start_y, start_x) });
 //    box(w[WIN_TYPE::LEFT], 0 , 0);		
 //    wrefresh(w[WIN_TYPE::LEFT]);	
 //
 //    refresh();
 //    w.insert({ WIN_TYPE::CENTER, newwin(height, width / 3, start_y, start_x + width / 3) });
 //    box(w[WIN_TYPE::CENTER], 0 , 0);		
 //    wrefresh(w[WIN_TYPE::CENTER]);	
 //
 //    refresh();
 //    w.insert({ WIN_TYPE::RIGHT, newwin(height, width / 3, start_y, start_x + 2 * width / 3) });
 //    box(w[WIN_TYPE::RIGHT], 0 , 0);		
 //    wrefresh(w[WIN_TYPE::RIGHT]);	
 //  }
}
