#pragma once

#include <string>
#include <vector>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

using m_menu = std::vector<std::pair<std::string, std::string>>;

namespace rrr::config
{

  inline const m_menu file_menu = { 
    { "New", "N" }, 
    { "Edit", "E" }, 
    { "Delete", "D" }, 
    { "Select", "BackSpace" }, 
    { "Copy", "C" }, 
    { "Paste", "P" }, 
    { "Quit", "Q" } 
  };
  
  inline const m_menu info_menu = { { "rrr", "F1" } }; 
}
