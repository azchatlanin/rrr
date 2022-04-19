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

  class history : public board
  {
    public:
      history(WINDOW*, int, int);

    public:
      void draw() override;
      void trigger(int) override;
      void set_pwd(std::string);
      void set_pos(std::string);

    public: 
      WINDOW* win;

    private: 
      void set_title();
      void fill(bool, WINDOW*, std::string);
      void sort();
      Files get_files_struct(const std::string);

    private:
      WINDOW* parent_win;
      std::string PWD;
      int height, width;

      int select_pos = 0;
      Files current_files;
  };
}
