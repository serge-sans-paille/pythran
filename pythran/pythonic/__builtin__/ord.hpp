#ifndef PYTHONIC_BUILTIN_ORD_HPP
#define PYTHONIC_BUILTIN_ORD_HPP

#include "pythonic/include/__builtin__/ord.hpp"

#include "pythonic/types/exceptions.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    long ord(types::str const &v)
    {
      if (v.size() != 1)
        throw types::TypeError(
            "ord() expected a character, but string of length " +
            std::to_string(v.size()) + " found");
      return (long)v[0];
    }

    long ord(char v)
    {
      return v;
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, ord);
  }
}

#endif
