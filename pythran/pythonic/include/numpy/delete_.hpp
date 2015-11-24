#ifndef PYTHONIC_INCLUDE_NUMPY_DELETE_HPP
#define PYTHONIC_INCLUDE_NUMPY_DELETE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, 1> delete_(types::ndarray<T, N> const &a, long index,
                                 types::none_type axis = __builtin__::None);

    template <class T, size_t N, class I>
    typename std::enable_if<!std::is_scalar<I>::value,
                            types::ndarray<T, 1>>::type
    delete_(types::ndarray<T, N> const &in, I const &indices,
            types::none_type axis = __builtin__::None);

    NUMPY_EXPR_TO_NDARRAY0_DECL(delete_);
    DECLARE_FUNCTOR(pythonic::numpy, delete_);
  }
}

#endif
