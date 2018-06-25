#ifndef PYTHONIC_NUMPY_ZEROS_HPP
#define PYTHONIC_NUMPY_ZEROS_HPP

#include "pythonic/include/numpy/zeros.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class pS, class dtype>
  types::ndarray<typename dtype::type, pS>
  zeros(pS const &shape, dtype d)
  {
    using T = typename dtype::type;
    // use calloc even if we have a non integer type. This looks ok on modern
    // architecture, although ! really standard
    auto *buffer = (T *)calloc(sutils::prod(shape), sizeof(T));
    auto shp = shape.array();
    return {buffer, shp.data(), types::ownership::owned};
  }

  template <class dtype>
  types::ndarray<typename dtype::type, types::pshape<long>> zeros(long size, dtype d)
  {
    return zeros(types::pshape<long>(size), d);
  }

  DEFINE_FUNCTOR(pythonic::numpy, zeros);
}
PYTHONIC_NS_END

#endif
