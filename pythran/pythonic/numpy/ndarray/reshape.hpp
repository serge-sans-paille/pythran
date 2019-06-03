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
    namespace misc
    {
      template <class P, size_t... Is>
      void set(P &p, long i, long v, utils::index_sequence<Is...>)
      {
        std::initializer_list<int> _{
            ((i == Is && (sutils::assign(std::get<Is>(p), v), true)), 1)...};
      }
    }
    template <class T, class pS, class NpS>
    typename std::enable_if<!std::is_integral<NpS>::value,
                            types::ndarray<T, NpS>>::type
    reshape(types::ndarray<T, pS> const &expr, NpS const &new_shape)
    {
      long where = sutils::find(new_shape, -1);
      if (where >= 0) {
        auto auto_shape = new_shape;
        misc::set(auto_shape, where,
                  expr.flat_size() / -sutils::prod(new_shape),
                  utils::make_index_sequence<std::tuple_size<NpS>::value>());
        return expr.reshape(auto_shape);
      } else {
        auto nshape = sutils::prod(new_shape);
        auto n = expr.flat_size();
        if (n < nshape) {
          types::ndarray<T, NpS> out(new_shape, __builtin__::None);
          auto iter = std::copy(expr.fbegin(), expr.fend(), out.fbegin());
          for (long i = 1; i < nshape / n; ++i)
            iter = std::copy(out.fbegin(), out.fbegin() + n, iter);
          std::copy(out.fbegin(), out.fbegin() + nshape % n, iter);
          return out;
        } else {
          return expr.reshape(new_shape);
        }
      }
    }
    template <class T, class pS, class NpS>
    typename std::enable_if<std::is_integral<NpS>::value,
                            types::ndarray<T, types::pshape<long>>>::type
    reshape(types::ndarray<T, pS> const &expr, NpS const &new_shape)
    {
      auto n = expr.flat_size();
      if (n < new_shape) {
        types::ndarray<T, types::pshape<long>> out(
            types::pshape<long>{new_shape}, __builtin__::None);
        auto iter = std::copy(expr.fbegin(), expr.fend(), out.fbegin());
        for (long i = 1; i < new_shape / n; ++i)
          iter = std::copy(out.fbegin(), out.fbegin() + n, iter);
        std::copy(out.fbegin(), out.fbegin() + new_shape % n, iter);
        return out;
      } else {
        return expr.reshape(types::pshape<long>(new_shape));
      }
    }

    template <class T, class pS, class S0, class S1, class... S>
    auto reshape(types::ndarray<T, pS> const &expr, S0 i0, S1 i1,
                 S const &... indices)
        -> decltype(reshape(expr,
                            types::pshape<S0, S1, S...>{i0, i1, indices...}))
    {
      return reshape(expr, types::pshape<S0, S1, S...>{i0, i1, indices...});
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(reshape);
  }
}
PYTHONIC_NS_END

#endif
