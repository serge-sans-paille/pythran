#ifndef PYTHONIC_INCLUDE_NUMPY_INTERP_HPP
#define PYTHONIC_INCLUDE_NUMPY_INTERP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
//  template <class T1, class T2, class T3>
//  types::ndarray<T3, types::array<long, 1>>
//  interp(types::ndarray<T1, types::array<long, 1>> x, types::ndarray<T2, types::array<long, 1>> xp, types::ndarray<T3, types::array<long, 1>> fp,
//    T3 left=__builtin__::None, T3 right=__builtin__::None, T2 period=__builtin__::None);
    
  template <class T1, class T2, class T3>
  types::ndarray<T3, types::array<long, 1>>
  interp(types::ndarray<T1, types::array<long, 1>> x, types::ndarray<T2, types::array<long, 1>> xp, types::ndarray<T3, types::array<long, 1>> fp);

  template <class T1, class T2, class T3>
  types::ndarray<T3, types::array<long, 1>>
  interp(types::ndarray<T1, types::pshape<long>> x, types::ndarray<T2, types::pshape<long>> xp, types::ndarray<T3, types::pshape<long>> fp);

  //template <class T>
  //types::ndarray<T, types::pshape<long>>
  //interp(x, xp, fp, left=None, right=None, period=None);

  NUMPY_EXPR_TO_NDARRAY0_DECL(interp);
  DEFINE_FUNCTOR(pythonic::numpy, interp);
}
PYTHONIC_NS_END

#endif
