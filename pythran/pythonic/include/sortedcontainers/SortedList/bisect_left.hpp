#ifndef PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_BISECT_LEFT_HPP
#define PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_BISECT_LEFT_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/SortedList.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace SortedList
  {

    template <class T, class F>
    long bisect_left(types::SortedList<T> const &seq, F &&value);

    DEFINE_FUNCTOR(pythonic::sortedcontainers::SortedList, bisect_left);
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
