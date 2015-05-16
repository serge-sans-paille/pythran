#ifndef PYTHONIC_BUILTIN_ID_HPP
#define PYTHONIC_BUILTIN_ID_HPP

#include "pythonic/include/__builtin__/id.hpp"

#include "pythonic/types/long.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    template <class T>
    long id(T const &t)
    {
      return t.id();
    }

    long id(pythran_long_t const &t)
    {
      return reinterpret_cast<long>(&t);
    }

    long id(long const &t)
    {
      return reinterpret_cast<long>(&t);
    }

    long id(double const &t)
    {
      return reinterpret_cast<long>(&t);
    }

    long id(bool const &t)
    {
      return reinterpret_cast<long>(&t);
    }

    PROXY_IMPL(pythonic::__builtin__, id);
  }
}

#endif
