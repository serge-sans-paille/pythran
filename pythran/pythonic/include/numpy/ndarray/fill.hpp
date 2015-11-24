#ifndef PYTHONIC_INCLUDE_NUMPY_NDARRAY_FILL_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDARRAY_FILL_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {
      template <class E, class F>
      types::none_type fill(E &&e, F f);

      template <class T, size_t N, class F>
      types::none_type fill(types::ndarray<T, N> &e, F f);

      DECLARE_FUNCTOR(pythonic::numpy::ndarray, fill);
    }
  }
}

#endif
