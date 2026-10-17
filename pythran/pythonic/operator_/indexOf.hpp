#ifndef PYTHONIC_OPERATOR_INDEXOF_HPP
#define PYTHONIC_OPERATOR_INDEXOF_HPP

#include "pythonic/include/operator_/indexOf.hpp"

#include "pythonic/builtins/ValueError.hpp"
#include "pythonic/builtins/str.hpp"
#include "pythonic/utils/functor.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace operator_
{
  namespace detail
  {
    template <class C, class V>
    struct has_index {
      template <class Cp, class Vp,
                class _ = decltype(std::declval<Cp>().index(std::declval<Vp>()))>
      static constexpr std::true_type get(Cp *, Vp *);
      static constexpr std::false_type get(...);
      static constexpr bool value =
          decltype(get(std::declval<C *>(), std::declval<std::decay_t<V> *>()))::value;
    };
  } // namespace detail

  template <class C, class V, class... Args>
  long indexOf(C const &c, V &&v, Args &&...args)
  {
    if constexpr (detail::has_index<C, V>::value) {
      return c.index(std::forward<V>(v), std::forward<Args>(args)...);
    } else {
      static_assert(sizeof...(Args) == 0);
      auto where = std::find(c.begin(), c.end(), v);
      if (where == c.end())
        throw types::ValueError(builtins::anonymous::str(v) + " is not in this sequence");
      return where - c.begin();
    }
  }

} // namespace operator_
PYTHONIC_NS_END

#endif
