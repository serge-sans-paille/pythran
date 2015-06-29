#ifndef PYTHONIC_BUILTIN_OCT_HPP
#define PYTHONIC_BUILTIN_OCT_HPP

#include "pythonic/include/builtins/oct.hpp"

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

#include <sstream>

namespace pythonic
{

  namespace builtins
  {

    template <class T>
    types::str oct(T const &v)
    {
      std::ostringstream oss;
      oss << '0' << std::oct << v;
      return oss.str();
    }

    PROXY_IMPL(pythonic::builtins, oct);
  }
}

#endif
