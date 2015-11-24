#ifndef PYTHONIC_INCLUDE_NUMPY_FROMFUNCTION_HPP
#define PYTHONIC_INCLUDE_NUMPY_FROMFUNCTION_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"
#include "pythonic/include/utils/tags.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class F, size_t N, class dtype, class Tags>
    struct fromfunction_helper;

    template <class F, class dtype, class purity_tag>
    struct fromfunction_helper<F, 1, dtype, purity_tag> {
      types::ndarray<typename std::remove_cv<typename std::remove_reference<
                         typename std::result_of<F(dtype)>::type>::type>::type,
                     1>
      operator()(F &&f, types::array<long, 1> const &shape, dtype d = dtype());
    };

    template <class F, class dtype, class purity_tag>
    struct fromfunction_helper<F, 2, dtype, purity_tag> {
      types::ndarray<
          typename std::remove_cv<typename std::remove_reference<
              typename std::result_of<F(dtype, dtype)>::type>::type>::type,
          2>
      operator()(F &&f, types::array<long, 2> const &shape, dtype d = dtype());
    };

    template <class F, size_t N, class dtype = double>
    auto fromfunction(F &&f, types::array<long, N> const &shape,
                      dtype d = dtype())
        -> decltype(fromfunction_helper<
            F, N, dtype, typename pythonic::purity_of<F>::type>()(
            std::forward<F>(f), shape));

    /* TODO: must specialize for higher order */
    DECLARE_FUNCTOR(pythonic::numpy, fromfunction);
  }
}

#endif
