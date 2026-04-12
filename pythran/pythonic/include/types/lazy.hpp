#ifndef PYTHONIC_INCLUDE_TYPES_LAZY_HPP
#define PYTHONIC_INCLUDE_TYPES_LAZY_HPP

#include "pythonic/include/types/combined.hpp"
#include <type_traits>

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  using lazy_res_t = decltype((std::declval<T>()()));
  template <class T>
  using lazy_res_decay_t = std::decay_t<lazy_res_t<T>>;

  template <class T0, class T1>
  using lazy_combined_t =
      std::conditional_t<std::is_same_v<lazy_res_t<T0>, lazy_res_t<T1>>, lazy_res_t<T0>,
                         typename __combined<lazy_res_decay_t<T0>, lazy_res_decay_t<T1>>::type>;
} // namespace types
PYTHONIC_NS_END

#endif
