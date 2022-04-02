#pragma once

#include <string>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif


namespace rrr::config::key
{
  using key = const std::string;

  namespace TOP_MENU
  {
    namespace FILE 
    {
      inline key FILE = "F";
      inline key NEW = "N";
      inline key EDIT = "E";
      inline key DELETE = "D";
      inline key SELECT = "S";
      inline key COPY = "C";
      inline key PASTE = "P";
      inline key QUITE = "Q";
    }

    namespace VIEW
    {
      inline key VIEW = "V";
      inline key INFO = "I";
      inline key LOGS = "L";
      inline key MONITOR = "M";
      inline key SCRIPT = "S";
    }
  }

  //========================================

  namespace MOVE
  {
    inline key MOVE_DOWN = "j";
    inline key MOVE_UP = "k";
  }
}

namespace rrr::config::ICON
{
  using key = const std::string;

  inline key MENU_SELECT = ">";
}

namespace rrr::config::type
{
  enum class FILE_TYPE { FILE, DIR };
}
