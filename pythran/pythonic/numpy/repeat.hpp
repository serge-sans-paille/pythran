#ifndef PYTHONIC_NUMPY_REPEAT_HPP
#define PYTHONIC_NUMPY_REPEAT_HPP

#include "pythonic/include/numpy/repeat.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> repeat(types::ndarray<T, N> const &expr, long repeats,
                                long axis)
    {
      if (axis < 0)
        axis += N;

      types::array<long, N> shape = expr.shape();
      const long stride = std::accumulate(shape.begin() + axis + 1, shape.end(),
                                          1L, std::multiplies<long>());
      shape[axis] *= repeats;

      types::ndarray<T, N> out(shape, __builtin__::None);
      auto out_iter = out.fbegin();
      for (auto iter = expr.fbegin(), end = expr.fend(); iter != end;
           iter += stride)
        for (int i = 0; i < repeats; ++i)
          out_iter = std::copy(iter, iter + stride, out_iter);
      return out;
    }
    template <class T, size_t N>
    types::ndarray<T, 1> repeat(types::ndarray<T, N> const &expr, long repeats,
                                types::none_type axis)
    {
      types::ndarray<T, 1> out(
          types::array<long, 1>{{expr.flat_size() * repeats}},
          __builtin__::None);
      auto out_iter = out.fbegin();
      for (auto iter = expr.fbegin(), end = expr.fend(); iter != end; ++iter)
        for (int i = 0; i < repeats; ++i)
          *out_iter++ = *iter;
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(repeat);
    DEFINE_FUNCTOR(pythonic::numpy, repeat);
  }
}

#endif
