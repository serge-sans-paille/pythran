#ifndef PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_COUNT_HPP
#define PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_COUNT_HPP

#include "pythonic/include/sortedcontainers/SortedList/count.hpp"

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
    long count(types::SortedList<T> const &seq, F &&value)
    {
      return seq.count(std::forward<F>(value));
    }
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
