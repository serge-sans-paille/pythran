#ifndef PYTHONIC_INCLUDE_NUMPY_INTERP_HPP
#define PYTHONIC_INCLUDE_NUMPY_INTERP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  // None,None,None
  template <class T1, class T2, class T3>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, types::none_type left = types::none_type{},
         types::none_type right = types::none_type{},
         types::none_type period = types::none_type{});

  // left None None
  template <class T1, class T2, class T3, typename t1>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, t1 left,
         types::none_type right = types::none_type{},
         types::none_type period = types::none_type{});

  // None right None
  template <class T1, class T2, class T3, typename t1>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, types::none_type left, t1 right,
         types::none_type period = types::none_type{});
  // None None period
  template <class T1, class T2, class T3, typename t1>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, types::none_type left, types::none_type right,
         t1 period);

  // left right None
  template <class T1, class T2, class T3, typename t1, typename t2>
  types::ndarray<double, types::pshape<long>>
  interp(T1 x, T2 xp, T3 fp, t1 left, t2 right,
         types::none_type period = types::none_type{});

  NUMPY_EXPR_TO_NDARRAY0_DECL(interp);
  DEFINE_FUNCTOR(pythonic::numpy, interp);
}
PYTHONIC_NS_END

#endif
