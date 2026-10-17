#ifndef PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_BISECT_RIGHT_HPP
#define PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_BISECT_RIGHT_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/SortedList.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace SortedList
  {

    template <class T, class F>
    long bisect_right(types::SortedList<T> const &seq, F &&value);

    DEFINE_FUNCTOR(pythonic::sortedcontainers::SortedList, bisect_right);
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
