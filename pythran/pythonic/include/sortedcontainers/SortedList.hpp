#ifndef PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_HPP
#define PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_HPP

#include "pythonic/include/types/SortedList.hpp"
#include "pythonic/include/utils/functor.hpp"

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
    SortedList(Iterable &&t);
  } // namespace anonymous

  DEFINE_FUNCTOR(pythonic::sortedcontainers::anonymous, SortedList);
} // namespace sortedcontainers
PYTHONIC_NS_END

#endif
