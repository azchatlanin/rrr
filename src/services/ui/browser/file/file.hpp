#pragma once

#include <vector>
#include <filesystem>
#include <ncurses.h>
#include <algorithm>

#include "utils/config.hpp"

namespace rrr
{
  struct dir 
  {
    dir(bool);
    dir(dir&&);
    dir(const dir&);

    dir& operator=(const dir&);
    bool operator()() const;

    bool is_dir;
  };

  class file 
  {
    public: 
      file(std::filesystem::path, bool);
      file(file&&);
      file(const file&);

    public:
      file& operator=(const file&);
      bool operator<(const file&);
      void draw(bool, int, std::shared_ptr<WINDOW>);
      bool operator==(const file&) const;
      bool is_directory() const { return directory(); }
      friend std::ostream& operator<<(std::ostream&, const file&);

    public:
      std::filesystem::path path;
      bool in_buffer = false;

    private:
      struct dir directory;
  };
}

namespace rrr::file_utils
{
  using files = std::vector<file>;

  struct filesystem_convert
  {
    file operator()(const std::filesystem::directory_entry& entry) const
    {
      return { entry.path(), std::filesystem::is_directory(entry) };
    }
  };

  inline files get_files_struct(const std::filesystem::path& path)
  {
    files f;
    try 
    {
      std::filesystem::directory_iterator start(path);
      std::filesystem::directory_iterator end;
      std::transform(start, end, std::back_inserter(f), filesystem_convert());
    }
    catch(...)
    {
      f.push_back({path / "no permission", true});
    }

    return f;
  }

  inline files fill(std::filesystem::path& pwd)
  {
    files current_files = get_files_struct(pwd);
    files tmp_dir;
    tmp_dir.reserve(current_files.size());

    files tmp_files;
    tmp_files.reserve(current_files.size());

    std::copy_if(current_files.begin(), current_files.end(), std::back_inserter(tmp_dir), [](const file& f) -> bool { 
      if (f.is_directory()) return true;
      else return false;
    });

    std::copy_if(current_files.begin(), current_files.end(), std::back_inserter(tmp_files), [](const file& f) -> bool { 
      if (!f.is_directory()) return true;
      else return false;
    });

    std::sort(tmp_dir.begin(), tmp_dir.end());
    std::sort(tmp_files.begin(), tmp_files.end());

    tmp_dir.insert(tmp_dir.end(), tmp_files.begin(), tmp_files.end());
    current_files= tmp_dir;

    return current_files;
  }
}
