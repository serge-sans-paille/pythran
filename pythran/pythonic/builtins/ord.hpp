#ifndef PYTHONIC_BUILTIN_ORD_HPP
#define PYTHONIC_BUILTIN_ORD_HPP

#include "pythonic/include/builtins/ord.hpp"

#include "pythonic/types/exceptions.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
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

    PROXY_IMPL(pythonic::builtins, ord);
  }
}

#endif
