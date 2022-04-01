#pragma once

#include <curses.h>
#include <vector>
#include <memory>

namespace rrr
{
  enum event { rebuild_all };

  struct state 
  {
    int max_y;
    int max_x;

    static std::shared_ptr<state> instance()
    {
      static std::shared_ptr<state> st = std::make_shared<state>();
      return st;
    }
  };

  struct Iboard
  {
    virtual ~Iboard() {}
    virtual void execute(class board*, event) const = 0;
  };

  class board 
  {
    public: 
      explicit board(Iboard* b_ = nullptr) : b { b_ } {}
      virtual ~board() {}

    public: 
      template<typename T>
      static std::shared_ptr<T> create()
      {
        static std::shared_ptr<T> instance = std::make_shared<T>();
        return instance;
      }

      void set(Iboard* b_) { b = b_; }
      virtual void commit(event) = 0;
      virtual void draw() = 0;
      virtual void rebuild() = 0;
      virtual void trigger(int) = 0;

    public: 
      WINDOW* win;

    private:
      virtual void create_win() = 0;
      void destroy()
      {
        wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(win);
        delwin(win);
      }

    protected: 
      Iboard* b;
      int start_x = 0, start_y = 0, width = 0, height = 0;
  };

  template<typename T, typename... Args>
  class manager final : public Iboard
  {
    public: 
      explicit manager(std::shared_ptr<T>&& t, std::shared_ptr<Args>&&... args)
      {
        vt.push_back(t);
        (vt.push_back(args), ...);
        for (auto v : vt) v->set(this);
      }

      void execute(board* md, event e) const override
      {
        switch (e) {
          case event::rebuild_all:
            for (auto v : vt) v->rebuild();
            break;
          default:
            for (auto v : vt) v->commit(e);
        };
      }

      void draw() 
      {
        for (auto v : vt) v->draw();
      };

      void trigger(int key) 
      {
        for (auto v : vt) v->trigger(key);
      };



    private: 
      std::vector<std::shared_ptr<T>> vt;
  };
}
