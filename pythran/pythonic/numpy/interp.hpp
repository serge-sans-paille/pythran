#ifndef PYTHONIC_NUMPY_INTERP_HPP
#define PYTHONIC_NUMPY_INTERP_HPP

#include "pythonic/include/numpy/interp.hpp"
#include "pythonic/include/numpy/remainder.hpp"
#include "pythonic/include/numpy/argsort.hpp"
#include <pythonic/include/numpy/concatenate.hpp>

#include <pythonic/numpy/remainder.hpp>
#include "pythonic/numpy/argsort.hpp"
#include <pythonic/numpy/concatenate.hpp>

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/numpy/interp_core.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T1, class T2, class T3, typename t1, typename t2, typename t3>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, t1 _left, t2 _right, t3 _period)
  {

    double left = _left;
    double right = _right;
    double period = _period;
    // Todo: what to do if this condition isn't satisfied? Can't use a statis
    // assert because the size isn't known at compile time.
    assert(std::get<0>(xp.shape()) == std::get<0>(fp.shape()));
    double outVal(0);

    if (period) {
      auto x_rem = pythonic::numpy::functor::remainder{}(x, period);
      auto xp_rem = pythonic::numpy::functor::remainder{}(xp, period);
      auto idx = pythonic::numpy::functor::argsort{}(xp_rem);
      auto xp_sorted = xp_rem[idx];
      auto fp_sorted = fp[idx];

      auto left_pad_xp =
          types::ndarray<typename T2::dtype, types::pshape<long>>(
              types::pshape<long>(1), xp_sorted[-1] - period);
      auto right_pad_xp =
          types::ndarray<typename T2::dtype, types::pshape<long>>(
              types::pshape<long>(1), xp_sorted[0] + period);
      auto new_xp = pythonic::numpy::functor::concatenate{}(
          pythonic::types::make_tuple(left_pad_xp, xp_sorted, right_pad_xp));

      auto left_pad_fp = types::ndarray<double, types::pshape<long>>(
          types::pshape<long>(1), fp_sorted[-1]);
      auto right_pad_fp = types::ndarray<double, types::pshape<long>>(
          types::pshape<long>(1), fp_sorted[0]);
      auto new_fp = pythonic::numpy::functor::concatenate{}(
          pythonic::types::make_tuple(left_pad_fp, fp_sorted, right_pad_fp));

      x = x_rem;
      xp = new_xp;
      fp = new_fp;
      left = 0.;  // Careful: using 0 (int) would cause problems!
      right = 0.; // Careful: using 0 (int) would cause problems!
    }

    types::ndarray<double, types::pshape<long>> out = {x.shape(), outVal};
    auto lenxp = xp.size();
    auto lenx = x.size();

    do_interp(x, xp, fp, out, lenxp, lenx, left, right);

    return out;
  }

  // No parameter specified
  template <class T1, class T2, class T3>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, types::none_type left, types::none_type right,
         types::none_type period)
  {
    auto _left = fp[0];
    auto _right = fp[-1];
    return interp(x, xp, fp, _left, _right, 0.);
  }

  // left specified
  template <class T1, class T2, class T3, typename t1>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, t1 left, types::none_type right,
         types::none_type period)
  {
    auto _right = fp[-1];
    return interp(x, xp, fp, left, _right, 0.);
  }
  // right specified
  template <class T1, class T2, class T3, typename t1>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, types::none_type left, t1 right,
         types::none_type period)
  {
    auto _left = fp[0];
    return interp(x, xp, fp, _left, right, 0.);
  }
  // period specified
  template <class T1, class T2, class T3, typename t1>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, types::none_type left, types::none_type right,
         t1 period)
  {
    assert(period != 0);
    return interp(x, xp, fp, 0., 0., period);
  }

  // left and right specified
  template <class T1, class T2, class T3, typename t1, typename t2>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, t1 left, t2 right, types::none_type period)
  {
    return interp(x, xp, fp, left, right, 0.);
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(interp);
}
PYTHONIC_NS_END

#endif
