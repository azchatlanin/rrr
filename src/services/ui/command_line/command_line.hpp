#pragma once

#include <vector>
#include <ncurses.h>

#include "services/managers/manager/manager.hpp"
#include "services/managers/state_manager/state_manager.hpp"

namespace rrr
{
  class command_line : public board
  {
    public:
      command_line();

    public:
      void draw() override;
      void trigger(int) override;
      void execute(event, std::any) override;

    public: 
      WINDOW* win;

    private: 
      // текущая команда
      std::string cmd;
      // вектор строк после разбора комантной строки по разделителю
      std::vector<std::string> v_cmd;
      // список доступных команд
      std::vector<std::string> commands { "rename", "touch", "trash", "mkdir", "delete", "paste", "move" };
     
    private:
      void set_title();
      void auto_fill();
      void clear();
      void drop();
      void command_run();
      void rename();
      void moving();
      void paste();
      void remove(std::string);
      void create(std::string);
      void remove_last();
      std::filesystem::path destination(const std::filesystem::path& p);
  };
}
