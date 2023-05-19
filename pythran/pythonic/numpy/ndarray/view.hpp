#ifndef PYTHONIC_NUMPY_NDARRAY_VIEW_HPP
#define PYTHONIC_NUMPY_NDARRAY_VIEW_HPP

#include "pythonic/include/numpy/ndarray/view.hpp"
#include "pythonic/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {
    template <class T, class pS>
    types::ndarray<T, pS> &view(types::ndarray<T, pS> &e)
    {
      return e;
    }

    template <class T, class pS>
    types::ndarray<T, pS> view(types::ndarray<T, pS> &&e)
    {
      return std::move(e);
    }

    template <class T, class pS, class dtype>
    types::ndarray<typename dtype::type,
                   types::array<long, types::ndarray<T, pS>::value>>
    view(types::ndarray<T, pS> &e, dtype d)
    {
      return e.template recast<typename dtype::type>();
    }

    template <class T, class pS, class dtype>
    types::ndarray<typename dtype::type,
                   types::array<long, types::ndarray<T, pS>::value>>
    view(types::ndarray<T, pS> &&e, dtype d)
    {
      return e.template recast<typename dtype::type>();
    }
  } // namespace ndarray
} // namespace numpy
PYTHONIC_NS_END

#endif
