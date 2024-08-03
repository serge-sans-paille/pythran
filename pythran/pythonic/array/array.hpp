#ifndef PYTHONIC_ARRAY_ARRAY_HPP
#define PYTHONIC_ARRAY_ARRAY_HPP

#include "pythonic/include/array/array.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace array
{

  template <char c>
  types::array<typename details::typecodes<c>::type>
  array(std::integral_constant<char, c>)
  {
    return {};
  }

  template <char c, class E>
  types::array<typename details::typecodes<c>::type>
  array(std::integral_constant<char, c>, E &&elts)
  {
    return {std::forward<E>(elts)};
  }

} // namespace array
PYTHONIC_NS_END

#endif
