#pragma once

#include <vector>
#include <filesystem>
#include <map>

#include "utils/config.hpp"

namespace rrr
{
  inline std::map<std::string, std::string> state;

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

    void draw()
    {}
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

  inline Files get_files_struct(const std::string& path)
  {
    Files f;
    std::filesystem::path p(path);
    std::filesystem::directory_iterator start(p);
    std::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(f), filesystem_convert());
    return f;
  }

  inline void sort(Files& current_files, std::string& PWD)
  {
    current_files = get_files_struct(PWD);
    Files tmp;
    tmp.reserve(current_files.size());
    Files tmp_files;
    tmp_files.reserve(current_files.size() / 2);

    std::copy_if(current_files.begin(), current_files.end(), std::back_inserter(tmp), [&tmp_files](const File& entry) -> bool { 
      if (entry.type == config::type::FILE_TYPE::DIR)
        return true;
      else
      {
        tmp_files.push_back(entry);
        return false;
      }
    });

    std::sort(tmp_files.begin(), tmp_files.end());
    std::sort(tmp.begin(), tmp.end());
    tmp.insert(tmp.end(), tmp_files.begin(), tmp_files.end());
    current_files= tmp;
  }

}
