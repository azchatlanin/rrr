#pragma once

#include <string>
#include <sstream>

namespace rrr::utils
{
  inline std::string key_to_str(int c)
  {
    std::stringstream ss;
    std::string str;
    ss << c;
    ss >> str;
    return str;
  }
}

 
  // inline std::string PWD = ".";
  // using vector_str = std::vector<std::string>;
  //
  // inline void set_new_pwd()
  // {
  //   const auto pos = PWD.find_last_of("/");
  //   if (!pos)
  //     PWD = "/";
  //   else
  //     PWD = PWD.substr(0, pos);
  // }
  //
  // inline void set_new_pwd(std::string pwd_part)
  // {
  //   PWD = PWD ==  "/" ? PWD + pwd_part : PWD + "/" + pwd_part;
  // }
