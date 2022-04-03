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
      return name.compare(other.name) < 0;
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
      void trigger() override;
      void commit(event) override;

    private: 
      void create_win() override;
      Files get_files_struct(const std::string path);
  };
}
