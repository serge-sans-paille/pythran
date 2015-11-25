#ifndef PYTHONIC_BUILTIN_INT_HPP
#define PYTHONIC_BUILTIN_INT_HPP

#include "pythonic/include/__builtin__/int_.hpp"

#include "pythonic/utils/functor.hpp"

#include <cassert>

namespace pythonic
{

  namespace __builtin__
  {

    namespace functor
    {

      template <class T>
      int_::type int_::operator()(T &&t)
      {
        return t;
      }

      int_::type int_::operator()(char t)
      {
        assert(t >= '0' and t <= '9');
        return t - '0';
      }

      int_::type int_::operator()()
      {
        return 0L;
      }
    }
  }
}

#endif
