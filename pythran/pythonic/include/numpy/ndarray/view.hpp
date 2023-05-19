#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_VIEW_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_VIEW_HPP

#include "pythonic/include/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {

    template <class T, class pS>
    types::ndarray<T, pS> &view(types::ndarray<T, pS> &e);

    template <class T, class pS>
    types::ndarray<T, pS> view(types::ndarray<T, pS> &&e);

    template <class T, class pS, class dtype>
    types::ndarray<typename dtype::type,
                   types::array<long, types::ndarray<T, pS>::value>>
    view(types::ndarray<T, pS> &e, dtype d);

    template <class T, class pS, class dtype>
    types::ndarray<typename dtype::type,
                   types::array<long, types::ndarray<T, pS>::value>>
    view(types::ndarray<T, pS> &&e, dtype d);

    DEFINE_FUNCTOR(pythonic::numpy::ndarray, view);
  } // namespace ndarray
} // namespace numpy
PYTHONIC_NS_END

#endif
