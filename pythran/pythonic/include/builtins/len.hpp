#ifndef PYTHONIC_INCLUDE_BUILTIN_LEN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LEN_HPP

#include "pythonic/include/utils/functor.hpp"

#include <tuple>

PYTHONIC_NS_BEGIN

namespace builtins
{

  template <class... Types>
  long len(std::tuple<Types...> const &);

  template <class T>
  long len(T const &t);

  DEFINE_FUNCTOR(pythonic::builtins, len);
} // namespace builtins
PYTHONIC_NS_END
#endif
