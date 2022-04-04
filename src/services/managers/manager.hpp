#pragma once

#include <curses.h>
#include <vector>
#include <memory>

#include "state_manager.hpp"

namespace rrr
{
  enum event {};

  struct Iboard
  {
    virtual ~Iboard() {}
    virtual void execute(class board*, event) const = 0;
  };

  class board 
  {
    public: 
      explicit board(Iboard* b_ = nullptr) : BOARD { b_ } {}
      virtual ~board() {}

    public: 
      template<typename T>
      static std::shared_ptr<T> instance()
      {
        static std::shared_ptr<T> instance = std::make_shared<T>();
        return instance;
      }
      void set(Iboard* b_) { BOARD = b_; }

      virtual void draw() = 0;
      virtual void trigger(std::string) = 0;

    private:
      virtual void create() = 0;

    protected: 
      std::string title;
      Iboard* BOARD;
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
      }

      void draw() 
      {
        for (auto v : vt) v->draw();
      }

      void trigger(int key) 
      {
        auto em = rrr::state_manager::instance().get();
        em->set(key);
        for (auto v : vt) 
          v->trigger(utils::char_to_str(key));
      }

    private: 
      std::vector<std::shared_ptr<T>> vt;
  };
}
