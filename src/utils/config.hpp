#pragma once

#include <filesystem>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif


namespace rrr::config::key
{
  inline const int ENTER = 10;
  inline const int COLON_COLON = 58;
  inline const int TAB = 9;
  inline const int ESC = 27;
  inline const int BACKSPACE = 263;
}

namespace rrr::config::path 
{
  inline const std::filesystem::path TRASH { "/home/chatlanin/.trash"};
}
