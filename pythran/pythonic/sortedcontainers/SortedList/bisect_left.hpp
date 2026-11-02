#ifndef PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_BISECT_LEFT_HPP
#define PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_BISECT_LEFT_HPP

#include "pythonic/include/sortedcontainers/SortedList/bisect_left.hpp"

#include "pythonic/builtins/None.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/SortedList.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace SortedList
  {

    template <class T, class F>
    long bisect_left(types::SortedList<T> const &seq, F &&value)
    {
      auto where = std::lower_bound(seq.begin(), seq.end(), std::forward<F>(value));
      return where - seq.begin();
    }
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
