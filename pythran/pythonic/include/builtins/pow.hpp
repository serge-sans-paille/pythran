#ifndef PYTHONIC_INCLUDE_BUILTIN_POW_HPP
#define PYTHONIC_INCLUDE_BUILTIN_POW_HPP

#include "pythonic/include/numpy/power.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{
  template <class... Types>
  auto pow(Types &&... args)
      -> decltype(numpy::functor::power{}(std::forward<Types>(args)...));

  DEFINE_FUNCTOR(pythonic::builtins, pow);
}
PYTHONIC_NS_END

#endif
