#pragma once

#include <string>
#include <vector>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

namespace rrr::config
{
  struct color_pair 
  {
    int A = 1;
    int B = 2;
  };
}
