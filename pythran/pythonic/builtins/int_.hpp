#ifndef PYTHONIC_BUILTIN_INT_HPP
#define PYTHONIC_BUILTIN_INT_HPP

#include "pythonic/include/builtins/int_.hpp"

#include "pythonic/utils/proxy.hpp"

#include <cassert>

namespace pythonic
{

  namespace builtins
  {

    template <class T>
    long int_(T &&t)
    {
      return t;
    }

    long int_(char t)
    {
      assert(t >= '0' and t <= '9');
      return t - '0';
    }

    long int_()
    {
      return 0L;
    }

    PROXY_IMPL(pythonic::builtins, int_);
  }
}

#endif
