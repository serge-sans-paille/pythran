#ifndef PYTHONIC_INCLUDE_NUMPY_UNION1D_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNION1D_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I, class O>
    void _union1d(I begin, I end, O &out, utils::int_<1>);

    template <class I, class O, size_t N>
    void _union1d(I begin, I end, O &out, utils::int_<N>);

    template <class E, class F>
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1>
    union1d(E const &e, F const &f);

    DECLARE_FUNCTOR(pythonic::numpy, union1d)
  }
}

#endif
