#ifndef PYTHONIC_INCLUDE_NUMPY_PARTIAL_SUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_PARTIAL_SUM_HPP

#include "pythonic/include/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class Op, size_t N>
    struct _partial_sum;

    template <class Op>
    struct _partial_sum<Op, 1> {
      template <class E, class F, class A>
      A operator()(E e, F &o, A acc);
    };

    template <class Op, size_t N>
    struct _partial_sum {
      template <class E, class F, class A>
      A operator()(E e, F &o, A acc);
    };

    template <class Op, class E,
              class dtype = types::dtype_t<typename E::dtype>>
    types::ndarray<typename dtype::type, 1> partial_sum(E const &expr,
                                                        dtype d = dtype());

    template <class Op, class E,
              class dtype = types::dtype_t<
                  typename std::remove_reference<E>::type::dtype>>
    auto partial_sum(E const &expr, long axis, dtype d = dtype()) ->
        typename std::enable_if<
            E::value == 1, decltype(partial_sum<Op, E, dtype>(expr))>::type;

    template <class E, class dtype = types::dtype_t<typename E::dtype>>
    using partial_sum_type = types::ndarray<typename dtype::type, E::value>;

    template <class Op, class E,
              class dtype = types::dtype_t<typename E::dtype>>
    typename std::enable_if<E::value != 1, partial_sum_type<E, dtype>>::type
    partial_sum(E const &expr, long axis, dtype d = dtype());
  }
}

#endif
