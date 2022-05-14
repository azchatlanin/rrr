#include "manager.hpp"

namespace rrr
{
  void manager::execute(event e, std::any data) const
  {
    if (e == QUIT)
    {
      endwin();
      exit(0);
    }

    for (auto&& b : boards)
    {
      b->execute(e, data);
      
      // когда выпоняем какую, то команду, то считается что действие в выбранной области полностью завершено
      // это конечно же может быть не верно. но пока это так.
      state_manager::instance().set(config::key::ESC);
      b->execute(event::DROP, true);
    }
  }

  void manager::draw() 
  {
    for (auto& b : boards) b->draw();
  }

  void manager::trigger(int key) 
  {

    if (key == config::key::ESC) 
    {
      for (auto&& b : boards) b->execute(event::DROP, true);
      state_manager::instance().set(key);
      return;
    }

    // если это не ключ команды, тогда тригерим в доски
    if (!state_manager::instance().set(key))
      for (auto&& b : boards) b->trigger(key);
  }
}
