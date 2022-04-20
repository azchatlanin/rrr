#pragma once

#include <curses.h>
#include <vector>
#include <memory>
#include <any>

#include "state_manager.hpp"

namespace rrr
{
  enum event 
  {
    CHANGE_PWD
  };

  struct Iboard
  {
    virtual ~Iboard() {}
    virtual void execute(event, std::any) const = 0;
  };

  class board 
  {
    public: 
      explicit board(Iboard* b_ = nullptr) : BOARD { b_ } {}
      virtual ~board() {}

    public: 
      template<typename T, typename... Args>
      static std::shared_ptr<T> make(Args... args)
      {
        static std::shared_ptr<T> instance = std::make_shared<T>(args...);
        return instance;
      }

      void set(Iboard* b_) { BOARD = b_; }

      virtual void draw() = 0;
      virtual void trigger(int) = 0;
      virtual void execute(event, std::any) = 0;

    protected: 
      Iboard* BOARD;
      std::string title;
      struct features
      {
        int start_x = 0; 
        int start_y = 0; 
        int width = 0; 
        int height = 0;
      } ft;

  };

  class manager : public Iboard
  {
    public: 
      template<typename... Args>
      explicit manager(Args&... args)
      {
        auto bi = std::back_inserter(boards);
        ((bi = args), ...);
        for (auto&& b : boards) b->set(this);
      }

      void execute(event e, std::any data) const override
      {
        for (auto&& b : boards) b->execute(e, data);
      }

      void draw() 
      {
        for (auto& b : boards) b->draw();
      }

      void trigger(int key) 
      {
        auto sm = rrr::state_manager::instance();
        sm.set(key);
        for (auto&& b : boards) 
          b->trigger(key);
      }

    private: 
      std::vector<std::shared_ptr<board>> boards;
  };
}
