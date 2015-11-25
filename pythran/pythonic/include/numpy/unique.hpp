#ifndef PYTHONIC_INCLUDE_NUMPY_UNIQUE_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNIQUE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/tuple.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I, class O>
    void _unique1(I begin, I end, O &out, utils::int_<1>);

    template <class I, class O, size_t N>
    void _unique1(I begin, I end, O &out, utils::int_<N>);

    template <class E>
    types::ndarray<typename E::dtype, 1> unique(E const &expr);

    template <class I, class O0, class O1>
    void _unique2(I begin, I end, O0 &out0, O1 &out1, long &i, utils::int_<1>);

    template <class I, class O0, class O1, size_t N>
    void _unique2(I begin, I end, O0 &out0, O1 &out1, long &i, utils::int_<N>);

    template <class E>
    std::tuple<types::ndarray<typename E::dtype, 1>, types::ndarray<long, 1>>
    unique(E const &expr, bool return_index);

    template <class I, class O0, class O1, class O2>
    void _unique3(I begin, I end, O0 &out0, O1 &out1, O2 &out2, long &i,
                  utils::int_<1>);

    template <class I, class O0, class O1, class O2, size_t N>
    void _unique3(I begin, I end, O0 &out0, O1 &out1, O2 &out2, long &i,
                  utils::int_<N>);

    template <class E>
    std::tuple<types::ndarray<typename E::dtype, 1>, types::ndarray<long, 1>,
               types::ndarray<long, 1>>
    unique(E const &expr, bool return_index, bool return_inverse);

    DECLARE_FUNCTOR(pythonic::numpy, unique)
  }
}

#endif
