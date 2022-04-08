#pragma once

#include <curses.h>
#include <memory>
#include <vector>
#include <filesystem>

#include "services/managers/manager.hpp"
#include "utils/config.hpp"

namespace rrr
{
  struct File 
  {
    config::type::FILE_TYPE type;
    std::filesystem::path name;

    File& operator=(const File& other)
    {
      if (this == &other)
        return *this;
      type = other.type;
      name = other.name;
      return *this;
    }

    bool operator<(const File& other)
    {
      std::string name_tmp = name;
      std::string other_name_tmp = other.name;

      for (char &ch : name_tmp)
        ch = std::tolower(ch);

      for (char &ch : other_name_tmp)
        ch = std::tolower(ch);

      return name_tmp.compare(other_name_tmp) < 0;
    }
  };

  struct filesystem_convert
  {
    File operator()(const std::filesystem::directory_entry& entry) const
    {
      File f;
      f.name = entry.path().filename().string();
      f.type = std::filesystem::is_directory(entry) ? config::type::FILE_TYPE::DIR : config::type::FILE_TYPE::FILE;
      return f;
    }
  };

  using Files = std::vector<File>;

  class browser : public board
  {
    public:
      browser();

    public:
      void draw() override;
      void trigger(int) override;

    public: 
      WINDOW* win;
      WINDOW* win_preview;
      WINDOW* win_navigation;
      WINDOW* win_history;

    private: 
      void create() override;
      void set_title();
      void set_cursor_position(const Files&);
      void rebuild();
      void fill(bool, WINDOW*, std::string);
      void next_pwd(std::string);
      void prew_pwd();
      Files get_files_struct(const std::string path);

    private:
      const int MAIN_KEY = 'F';
      std::string PWD;
      int key;
      int select_pos = 0;
      bool on_this = false;
  };
}
