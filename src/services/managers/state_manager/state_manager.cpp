#include "state_manager.hpp"

namespace rrr
{
  state_manager& state_manager::instance()
  {
    static state_manager st;
    return st;
  }
}
