#ifndef PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_COPY_HPP
#define PYTHONIC_INCLUDE_SORTEDCONTAINERS_SORTEDLIST_COPY_HPP

#include "pythonic/include/__dispatch__/copy.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN
namespace sortedcontainers
{
  namespace SortedList
  {
    USING_FUNCTOR(copy, pythonic::__dispatch__::functor::copy);
  }
} // namespace sortedcontainers
PYTHONIC_NS_END

#endif
