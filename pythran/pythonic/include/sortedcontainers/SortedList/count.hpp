#ifndef PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_COUNT_HPP
#define PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_COUNT_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/SortedList.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace SortedList
  {

    template <class T, class F>
    long count(types::SortedList<T> const &seq, F &&value);

    DEFINE_FUNCTOR(pythonic::sortedcontainers::SortedList, count);
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
