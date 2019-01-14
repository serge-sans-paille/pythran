#ifndef PYTHONIC_NUMPY_INTERP_HPP
#define PYTHONIC_NUMPY_INTERP_HPP

#include "pythonic/include/numpy/interp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
//  template <class T1, class T2, class T3>
//  types::ndarray<T3, types::array<long, 1>>
//  interp(types::ndarray<T1, types::array<long, 1>> x, types::ndarray<T2, types::array<long, 1>> xp, types::ndarray<T3, types::array<long, 1>> fp,
//    T3 left, T3 right, T2 period){
//
//    return fp;
//   }
    
    template <class T1, class T2, class T3>
    types::ndarray<T3, types::array<long, 1>>
    interp(types::ndarray<T1, types::array<long, 1>> x, types::ndarray<T2, types::array<long, 1>> xp, types::ndarray<T3, types::array<long, 1>> fp){
        
        return fp;
    }
    
    template <class T1, class T2, class T3>
    types::ndarray<T3, types::array<long, 1>>
    interp(types::ndarray<T1, types::pshape<long>> x, types::ndarray<T2, types::pshape<long>> xp, types::ndarray<T3, types::pshape<long>> fp){

        return fp;
    }


/*
  template <class T, class pS>
  types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>
  interp(types::ndarray<T, pS> const &expr, long repeats, long axis)
  {
    constexpr auto N = std::tuple_size<pS>::value;
    if (axis < 0)
      axis += N;

    auto shape = sutils::array(expr.shape());
    const long stride = std::accumulate(shape.begin() + axis + 1, shape.end(),
                                        1L, std::multiplies<long>());
    shape[axis] *= repeats;

    types::ndarray<T, types::array<long, std::tuple_size<pS>::value>> out(
        shape, __builtin__::None);
    auto out_iter = out.fbegin();
    for (auto iter = expr.fbegin(), end = expr.fend(); iter != end;
         iter += stride)
      for (int i = 0; i < repeats; ++i)
        out_iter = std::copy(iter, iter + stride, out_iter);
    return out;
  }
  template <class T, class pS>
  types::ndarray<T, types::pshape<long>>
  interp(types::ndarray<T, pS> const &expr, long repeats, types::none_type axis)
  {
    types::ndarray<T, types::pshape<long>> out(
        types::pshape<long>{expr.flat_size() * repeats}, __builtin__::None);
    auto out_iter = out.fbegin();
    for (auto iter = expr.fbegin(), end = expr.fend(); iter != end; ++iter)
      for (int i = 0; i < repeats; ++i)
        *out_iter++ = *iter;
    return out;
  }
   */
  NUMPY_EXPR_TO_NDARRAY0_IMPL(interp);
}
PYTHONIC_NS_END

#endif
