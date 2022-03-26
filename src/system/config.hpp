#pragma once

#include <string>
#include <vector>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

namespace rrr::config
{
  using m_menu = std::vector<std::pair<std::string, std::string>>;

  inline const m_menu f_menu = { 
    { "New", "N" }, 
    { "Edit", "E" }, 
    { "Delete", "D" }, 
    { "Select", "BackSpace" }, 
    { "Copy", "C" }, 
    { "Paste", "P" }, 
    { "Quit", "Q" } 
  };
  
  inline const m_menu i_menu = { { "rrr", "F1" } }; 
}
