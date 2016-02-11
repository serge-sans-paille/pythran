#ifndef PYTHONIC_INCLUDE_NUMPY_REPEAT_HPP
#define PYTHONIC_INCLUDE_NUMPY_REPEAT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> repeat(types::ndarray<T, N> const &expr, long repeats,
                                long axis);

    template <class T, size_t N>
    types::ndarray<T, 1> repeat(types::ndarray<T, N> const &expr, long repeats,
                                types::none_type axis = types::none_type{});

    NUMPY_EXPR_TO_NDARRAY0_DECL(repeat);
    DECLARE_FUNCTOR(pythonic::numpy, repeat);
  }
}

#endif
