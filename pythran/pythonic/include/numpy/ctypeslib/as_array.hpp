#ifndef PYTHONIC_INCLUDE_NUMPY_CTYPESLIB_AS_ARRAY_HPP
#define PYTHONIC_INCLUDE_NUMPY_CTYPESLIB_AS_ARRAY_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/pointer.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace ctypeslib
  {
    template <class T, size_t N>
    types::ndarray<T, N> as_array(types::pointer<T>, types::array<long, N>);

    template <class T>
    types::ndarray<T, 1> as_array(types::pointer<T>, long);
    DECLARE_FUNCTOR(pythonic::numpy::ctypeslib, as_array);
  }
}
PYTHONIC_NS_END

#endif
