#pragma once

#include "services/managers/state_manager/state_manager.hpp"
#include "services/ui/browser/file/file.hpp"
#include "utils/config.hpp"

namespace rrr
{
  class navigation
  {
    public:
      navigation(WINDOW*, int, int, int, int);

    public: 
      std::shared_ptr<WINDOW> win;

    public:
      void draw();
      void fill();
      // две перегруженные функции для установки позиции курсора
      // первая ставит по индексу, вторая при перехоже на другую страницу
      void cursor_up();
      void cursor_down();
      void cursor_check();
      void set_cursor_pos(int);
      void set_cursor_pos();
      // устанавливает позицию курсора по пути, нужно при создании файла или дирректории и подобного
      void set_cursor_pos(std::filesystem::path);
      void buffer_update();
      void select();
      int get_cursor_pos();
      std::string get_content();
      file_utils::files get_current_files();

    private:
      std::string content = "is empty";
      int cursor_pos = 0;
      file_utils::files current_files;
      bool is_last = false;

    private: 
      void draw_content();
  };
}
