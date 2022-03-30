#pragma once

#include <vector>
#include <memory>

namespace rrr
{
  enum event { };

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
      void set(Iboard* b_) { b = b_; }
      virtual void commit(event) = 0;
      virtual void draw() = 0;
      virtual void rebuild() = 0;
      virtual void trigger(int) = 0;

    private:
      virtual void create_win() = 0;

    protected: 
      Iboard* b;
  };

  template<typename T, typename... Args>
  class manager final : public Iboard
  {
    public: 
      explicit manager(std::shared_ptr<T>&& t, std::shared_ptr<Args>&&... args)
      {
        vt.push_back(std::move(t));
        (vt.push_back(std::move(args)), ...);
        for (auto v : vt) v->set(this);
      }

      void execute(board* md, event e) const override
      {
        for (auto v : vt) v->commit(e);
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
