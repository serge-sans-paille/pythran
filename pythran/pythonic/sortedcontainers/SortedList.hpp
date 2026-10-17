#ifndef PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_HPP
#define PYTHONIC_SORTEDCONTAINERS_SORTEDLIST_HPP

#include "pythonic/include/sortedcontainers/SortedList.hpp"

#include "pythonic/types/SortedList.hpp"
#include "pythonic/utils/functor.hpp"

#include <iterator>
#include <type_traits>

PYTHONIC_NS_BEGIN

namespace sortedcontainers
{

  namespace anonymous
  {
    template <class Iterable>
    types::SortedList<std::decay_t<typename std::iterator_traits<
        typename std::remove_reference_t<Iterable>::iterator>::value_type>>
    SortedList(Iterable &&t)
    {
      return {t.begin(), t.end()};
    }
  } // namespace anonymous
} // namespace sortedcontainers
PYTHONIC_NS_END

#endif
