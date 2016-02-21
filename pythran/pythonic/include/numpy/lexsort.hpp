#ifndef PYTHONIC_INCLUDE_NUMPY_LEXSORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_LEXSORT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class T, size_t N>
    types::ndarray<long, 1> lexsort(types::array<T, N> const &keys);

    template <class... Types>
    types::ndarray<long, 1> lexsort(std::tuple<Types...> const &keys);

    DECLARE_FUNCTOR(pythonic::numpy, lexsort)
  }
}

#endif
