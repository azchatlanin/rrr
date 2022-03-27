#pragma once

#include <curses.h>
#include <memory>
#include <vector>

namespace rrr
{
  class board 
  {
    public:
      virtual ~board() {};
      virtual void draw() = 0;
  };
     
  class layer
  {
    public:
      layer();
      ~layer();

    public:
      WINDOW* layer_win;

    public:
      static std::shared_ptr<layer> instance();
      void draw();
      void trigger(int);
      void add(std::shared_ptr<board>);

    private:
      int start_x, start_y, width, height;
      std::vector<std::shared_ptr<board>> boards;

    private: 
      void init();
      void create_win();
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
