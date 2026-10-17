#ifndef PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_INDEX_HPP
#define PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_INDEX_HPP

#include "pythonic/include/sortedcontainers/SortedList/index.hpp"

#include "pythonic/builtins/None.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/SortedList.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace SortedList
  {
    template <class T, class F, class StartType, class StopType>
    long index(types::SortedList<T> const &seq, F &&value, StartType start, StopType stop)
    {
      return seq.index(std::forward<F>(value), start, stop);
    }
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
