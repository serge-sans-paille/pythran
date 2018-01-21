#ifndef PYTHONIC_NUMPY_CTYPESLIB_AS_ARRAY_HPP
#define PYTHONIC_NUMPY_CTYPESLIB_AS_ARRAY_HPP

#include "pythonic/include/numpy/ctypeslib/as_array.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/pointer.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace ctypeslib
  {
    template <class T, size_t N>
    types::ndarray<T, N> as_array(types::pointer<T> ptr,
                                  types::array<long, N> shape)
    {
      return {ptr.data, shape.data(), types::ownership::external};
    }

    template <class T>
    types::ndarray<T, 1> as_array(types::pointer<T> ptr, long size)
    {
      return as_array(ptr, types::array<long, 1>{{size}});
    }

    DEFINE_FUNCTOR(pythonic::numpy::ctypeslib, as_array);
  }
}
PYTHONIC_NS_END

#endif
