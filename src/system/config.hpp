#pragma once

#include <string>
#include <vector>

#ifndef CTRL
#define	CTRL(c)	(c & 037)
#endif

namespace rrr::config
{
  struct color_pair // I don't no what name is these colors.
  {
    int A = 1;
    int B = 2;
  };
}
