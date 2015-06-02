#ifndef PYTHONIC_INCLUDE_BUILTIN_ABS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ABS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/numpy/abs.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    // FIXME np.abs accept any iterator while __builtin__.abs only accept
    // numeric types and numpy.array
    ALIAS_DECL(abs, numpy::proxy::abs{});
    PROXY_DECL(pythonic::__builtin__, abs);
  }
}

#endif
