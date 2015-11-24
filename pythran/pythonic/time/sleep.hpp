#ifndef PYTHONIC_TIME_SLEEP_HPP
#define PYTHONIC_TIME_SLEEP_HPP

#include "pythonic/include/time/sleep.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/__builtin__/None.hpp"

#include <thread>
#include <chrono>

namespace pythonic
{

  namespace time
  {

    types::none_type sleep(double const value)
    {
      std::this_thread::sleep_for(std::chrono::duration<double>(value));
      return __builtin__::None;
    }

    DEFINE_FUNCTOR(pythonic::time, sleep)
  }
}

#endif
