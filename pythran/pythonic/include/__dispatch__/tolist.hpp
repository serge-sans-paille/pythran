#ifndef PYTHONIC_INCLUDE_DISPATCH_TOLIST_HPP
#define PYTHONIC_INCLUDE_DISPATCH_TOLIST_HPP

#include "pythonic/include/numpy/ndarray/tolist.hpp"
#include "pythonic/include/types/array.hpp"

PYTHONIC_NS_BEGIN

namespace __dispatch__
{
  template <class Any>
  auto tolist(Any &&any) -> decltype(numpy::ndarray::tolist(any))
  {
    return numpy::ndarray::tolist(any);
  }

  template <class T>
  types::list<long> tolist(types::array<T> &&a)
  {
    return a;
  }

  template <class T>
  types::list<long> tolist(types::array<T> const &a)
  {
    return a;
  }

  DEFINE_FUNCTOR(pythonic::__dispatch__, tolist);
} // namespace __dispatch__
PYTHONIC_NS_END

#endif
