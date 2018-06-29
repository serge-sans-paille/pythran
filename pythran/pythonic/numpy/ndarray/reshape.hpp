#ifndef PYTHONIC_NUMPY_NDARRAY_RESHAPE_HPP
#define PYTHONIC_NUMPY_NDARRAY_RESHAPE_HPP

#include "pythonic/include/numpy/ndarray/reshape.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {
    template <class T, class pS, class NpS>
    typename std::enable_if<!std::is_integral<NpS>::value,
                            types::ndarray<T, NpS>>::type
    reshape(types::ndarray<T, pS> const &expr, NpS const &new_shape)
    {
      auto auto_shape = new_shape;
      auto where = sutils::find(auto_shape, -1);
      if (where) {
        *where = expr.flat_size() / -sutils::prod(new_shape);
        return expr.reshape(auto_shape);
      } else {
        types::ndarray<T, NpS> out(new_shape, __builtin__::None);
        auto nshape = out.flat_size();
        auto n = expr.flat_size();
        if (n < nshape) {
          auto iter = std::copy(expr.fbegin(), expr.fend(), out.fbegin());
          for (long i = 1; i < nshape / n; ++i)
            iter = std::copy(out.fbegin(), out.fbegin() + n, iter);
          std::copy(out.fbegin(), out.fbegin() + nshape % n, iter);
        } else
          std::copy(expr.fbegin(), expr.fbegin() + nshape, out.fbegin());
        return out;
      }
    }
    template <class T, class pS, class NpS>
    typename std::enable_if<std::is_integral<NpS>::value,
                            types::ndarray<T, types::pshape<long>>>::type
    reshape(types::ndarray<T, pS> const &expr, NpS const &new_shape)
    {
      types::ndarray<T, types::pshape<long>> out(types::pshape<long>{new_shape},
                                                 __builtin__::None);
      auto n = expr.flat_size();
      if (n < new_shape) {
        auto iter = std::copy(expr.fbegin(), expr.fend(), out.fbegin());
        for (long i = 1; i < new_shape / n; ++i)
          iter = std::copy(out.fbegin(), out.fbegin() + n, iter);
        std::copy(out.fbegin(), out.fbegin() + new_shape % n, iter);
      } else
        std::copy(expr.fbegin(), expr.fbegin() + new_shape, out.fbegin());
      return out;
    }

    template <class T, class pS, class... S>
    auto reshape(types::ndarray<T, pS> const &expr, S const &... indices)
        -> decltype(reshape(expr, types::pshape<S...>{indices...}))
    {
      return reshape(expr, types::pshape<S...>{indices...});
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(reshape);

    DEFINE_FUNCTOR(pythonic::numpy::ndarray, reshape);
  }
}
PYTHONIC_NS_END

#endif
