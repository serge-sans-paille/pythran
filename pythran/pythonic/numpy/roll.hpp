#ifndef PYTHONIC_NUMPY_ROLL_HPP
#define PYTHONIC_NUMPY_ROLL_HPP

#include "pythonic/include/numpy/roll.hpp"

#include "pythonic/builtins/ValueError.hpp"
#include "pythonic/operator_/mod.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"

#include <numeric>

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<T, pS> roll(types::ndarray<T, pS> const &expr, long shift)
  {
    types::ndarray<T, pS> out(expr._shape, builtins::None);
    long expr_fsize = expr.flat_size();
    // Nothing to roll: `out` has the right shape and no element, so it already
    // matches `expr`. Returning it instead of `expr.copy()` also keeps GCC
    // from deriving a zero-sized allocation for `copy()`, which triggers bogus
    // -Warray-bounds. See #2472.
    if (expr_fsize == 0)
      return out;
    // Python's floored modulo brings `shift` into [0, dim) whatever its sign;
    // a plain `shift += dim` would only correct by one period.
    shift = operator_::mod(shift, expr_fsize);

    std::copy(expr.fbegin(), expr.fend() - shift,
              std::copy(expr.fend() - shift, expr.fend(), out.fbegin()));
    return out;
  }

  namespace
  {
    template <class To, class From, size_t N>
    To _roll(To to, From from, long shift, long axis, types::array_tuple<long, N> const &shape,
             utils::int_<N - 1>)
    {
      long dim = shape[N - 1];
      if (axis == N - 1) {
        const From split = from + (dim - shift);
        to = std::copy(split, from + dim, to);
        return std::copy(from, split, to);
      } else {
        return std::copy(from, from + dim, to);
      }
    }

    template <class To, class From, size_t N, size_t M>
    std::enable_if_t<M != N - 1, To> _roll(To to, From from, long shift, long axis,
                                           types::array_tuple<long, N> const &shape, utils::int_<M>)
    {
      long dim = shape[M];
      long offset =
          std::accumulate(shape.begin() + M + 1, shape.end(), 1L, std::multiplies<long>());
      if (axis == M) {
        const From split = from + (dim - shift) * offset;
        for (From iter = split, end = from + dim * offset; iter != end; iter += offset)
          to = _roll(to, iter, shift, axis, shape, utils::int_<M + 1>());
        for (From iter = from, end = split; iter != end; iter += offset)
          to = _roll(to, iter, shift, axis, shape, utils::int_<M + 1>());
      } else {
        for (From iter = from, end = from + dim * offset; iter != end; iter += offset)
          to = _roll(to, iter, shift, axis, shape, utils::int_<M + 1>());
      }
      return to;
    }
  } // namespace

  template <class T, class pS>
  types::ndarray<T, pS> roll(types::ndarray<T, pS> const &expr, long shift, long axis)
  {
    constexpr long ndim = types::ndarray<T, pS>::value;
    auto expr_shape = sutils::array(expr._shape);
    types::ndarray<T, pS> out(expr._shape, builtins::None);
    if (axis < 0)
      axis += ndim;
    if (axis < 0 || axis >= ndim)
      throw types::ValueError("axis out of bounds");
    // Nothing to roll: return the empty `out`, not `expr.copy()`. See the
    // single-shift overload and #2472.
    if (expr.flat_size() == 0)
      return out;
    shift = operator_::mod(shift, expr_shape[axis]);

    _roll(out.fbegin(), expr.fbegin(), shift, axis, expr_shape, utils::int_<0>());
    return out;
  }

  namespace
  {
    template <class To, class From, size_t N>
    To _rolls(To to, From from, long shifts[N], types::array_tuple<long, N> const &shape,
              utils::int_<N - 1>)
    {
      long dim = shape[N - 1];
      if (long shift = shifts[N - 1]) {
        From from_split = from + (dim - shift);
        To next = std::copy(from_split, from + dim, to);
        return std::copy(from, from_split, next);
      } else {
        return std::copy(from, from + dim, to);
      }
    }

    template <class To, class From, size_t N, size_t M>
    std::enable_if_t<M != N - 1, To> _rolls(To to, From from, long shifts[N],
                                            types::array_tuple<long, N> const &shape,
                                            utils::int_<M>)
    {
      long dim = shape[M];
      long offset =
          std::accumulate(shape.begin() + M + 1, shape.end(), 1L, std::multiplies<long>());
      if (long shift = shifts[M]) {
        const From split = from + (dim - shift) * offset;
        for (From iter = split, end = from + dim * offset; iter != end; iter += offset)
          to = _rolls(to, iter, shifts, shape, utils::int_<M + 1>());
        for (From iter = from; iter != split; iter += offset)
          to = _rolls(to, iter, shifts, shape, utils::int_<M + 1>());
      } else {
        for (From iter = from, end = from + dim * offset; iter != end; iter += offset)
          to = _rolls(to, iter, shifts, shape, utils::int_<M + 1>());
      }
      return to;
    }
  } // namespace

  template <class T, class pS, size_t N>
  types::ndarray<T, pS> roll(types::ndarray<T, pS> const &expr, types::array_tuple<long, N> shifts,
                             types::array_tuple<long, N> axes)
  {
    constexpr long ndim = types::ndarray<T, pS>::value;
    auto expr_shape = sutils::array(expr._shape);
    types::ndarray<T, pS> out(expr._shape, builtins::None);
    for (size_t i = 0; i < N; ++i) {
      long axis = axes[i];
      if (axis < 0)
        axis += ndim;
      if (axis < 0 || axis >= ndim)
        throw types::ValueError("axis out of bounds");
      axes[i] = axis;
    }
    // Nothing to roll (and no dimension to take a modulo of): return the
    // empty `out`, not `expr.copy()`. See the single-shift overload and #2472.
    if (expr.flat_size() == 0)
      return out;

    // Accumulate per-dimension shifts, keeping every entry in [0, dim):
    // taking each shift modulo its dimension before adding keeps repeated
    // axes from overflowing, and the trailing modulo reduces the sum of two
    // such values back into range.
    long axes_shifts[ndim] = {0};
    for (size_t i = 0; i < N; ++i) {
      long dim = expr_shape[axes[i]];
      axes_shifts[axes[i]] = (axes_shifts[axes[i]] + operator_::mod(shifts[i], dim)) % dim;
    }

    _rolls(out.fbegin(), expr.fbegin(), axes_shifts, expr_shape, utils::int_<0>());
    return out;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(roll);
} // namespace numpy
PYTHONIC_NS_END

#endif
