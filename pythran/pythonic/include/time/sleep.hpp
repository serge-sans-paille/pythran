#ifndef PYTHONIC_INCLUDE_TIME_SLEEP_HPP
#define PYTHONIC_INCLUDE_TIME_SLEEP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/NoneType.hpp"

namespace pythonic
{

  namespace time
  {
    types::none_type sleep(double const value);

    DECLARE_FUNCTOR(pythonic::time, sleep)
  }
}

#endif
