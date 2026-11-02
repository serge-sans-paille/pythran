#ifndef PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_INDEX_HPP
#define PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_INDEX_HPP

#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/SortedList.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace SortedList
  {

    template <class T, class F, class StartType = types::none_type,
              class StopType = types::none_type>
    long index(types::SortedList<T> const &seq, F &&value, StartType start = {},
               StopType stop = {});

    DEFINE_FUNCTOR(pythonic::sortedcontainers::SortedList, index);
  } // namespace SortedList
} // namespace sortedcontainers
PYTHONIC_NS_END
#endif
