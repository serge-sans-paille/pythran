#ifndef PYTHONIC_INCLUDE_NUMPY_PUT_HPP
#define PYTHONIC_INCLUDE_NUMPY_PUT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class F, class T, size_t N, class E>
    typename std::enable_if<types::is_numexpr_arg<F>::value,
                            types::none_type>::type
    put(types::ndarray<T, N> &expr, F const &ind, E const &v);

    template <class T, size_t N>
    types::none_type put(types::ndarray<T, N> &expr, long int ind, T const &v);

    template <class E, class M, class V>
    types::none_type put(E &, M const &, V const &);

    DECLARE_FUNCTOR(pythonic::numpy, put);
  }
}

#endif
