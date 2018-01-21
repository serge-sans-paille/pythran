#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_INDEX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_INDEX_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/list.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace list
  {

    template <class T>
    long index(types::list<T> &seq, T const &x);

    template <class T>
    long index(types::list<T> &&seq, T const &x);

    DECLARE_FUNCTOR(pythonic::__builtin__::list, index);
  }
}
PYTHONIC_NS_END
#endif
