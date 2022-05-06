#pragma once

#include <string>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif


namespace rrr::config::key
{
  using key = const std::string;

  inline key ESC = "ESC";

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
}
