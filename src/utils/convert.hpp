#pragma once

#include <string>
#include <sstream>

namespace rrr::utils
{
  inline std::string char_to_str(char c)
  {
    std::stringstream ss;
    std::string str;
    ss << c;
    ss >> str;
    return str;
  }
}
