#ifndef PYTHONIC_INCLUDE_NUMPY_LEXSORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_LEXSORT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class K>
    struct lexcmp {
      K const &keys;
      lexcmp(K const &keys);
      bool operator()(long i0, long i1);
    };

    template <class T, size_t N>
    types::ndarray<long, 1> lexsort(types::array<T, N> const &keys);

    DECLARE_FUNCTOR(pythonic::numpy, lexsort)
  }
}

#endif
