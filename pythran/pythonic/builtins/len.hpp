#ifndef PYTHONIC_BUILTIN_LEN_HPP
#define PYTHONIC_BUILTIN_LEN_HPP

#include "pythonic/include/builtins/len.hpp"
#include "pythonic/include/types/traits.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{
  template <class... Types>
  long len(std::tuple<Types...> const &)
  {
    return sizeof...(Types);
  }

  template <class T>
  long len(T const &t)
  {
    if constexpr (types::has_size<T>::value) {
      return t.size();
    } else {
      static_assert(std::is_void_v<T> && "TypeError: object has no len()");
    }
  }
} // namespace builtins
PYTHONIC_NS_END
#endif
