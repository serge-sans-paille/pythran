#ifndef PYTHONIC_TYPES_VECTORIZABLE_TYPE_HPP
#define PYTHONIC_TYPES_VECTORIZABLE_TYPE_HPP

#include "pythonic/include/types/vectorizable_type.hpp"

#include "pythonic/include/numpy/bool_.hpp"
#include "pythonic/include/numpy/uint8.hpp"
#include "pythonic/include/numpy/int8.hpp"
#include "pythonic/include/numpy/uint16.hpp"
#include "pythonic/include/numpy/int16.hpp"
#include "pythonic/include/numpy/uint32.hpp"
#include "pythonic/include/numpy/int32.hpp"
#include "pythonic/include/numpy/uint64.hpp"
#include "pythonic/include/numpy/int64.hpp"
#include "pythonic/include/numpy/float32.hpp"
#include "pythonic/include/numpy/float64.hpp"

PYTHONIC_NS_BEGIN
namespace operator_
{
  namespace functor
  {
    struct mod;
  }
}

namespace numpy
{
  namespace functor
  {
    struct angle_in_rad;
    struct asarray_chkfinite;
    struct clip;
    struct fix;
    struct isfinite;
    struct isinf;
    struct isnan;
    struct isposinf;
    struct ldexp;
    struct logaddexp2;
    struct nan_to_num;
    struct rint;
    struct signbit;
    struct where;
  }
}
namespace types
{
  template <class O>
  struct is_vector_op {

    // vectorize everything but these ops. They require special handling for
    // vectorization, && SG did ! invest enough time in those
    static const bool value =
        !std::is_same<O, operator_::functor::mod>::value &&
        !std::is_same<O, numpy::functor::logaddexp2>::value &&
        // Return type for generic function should be generic
        !std::is_same<O, numpy::functor::angle_in_rad>::value &&
        !std::is_same<O, numpy::functor::ldexp>::value &&
        !std::is_same<O, numpy::functor::isfinite>::value &&
        !std::is_same<O, numpy::functor::fix>::value &&
        !std::is_same<O, numpy::functor::isinf>::value &&
        !std::is_same<O, numpy::functor::isnan>::value &&
        !std::is_same<O, numpy::functor::isposinf>::value &&
        !std::is_same<O, numpy::functor::rint>::value &&
        !std::is_same<O, numpy::functor::signbit>::value &&
        // conditional processing doesn't permit SIMD
        !std::is_same<O, numpy::functor::nan_to_num>::value &&
        !std::is_same<O, numpy::functor::asarray_chkfinite>::value &&
        !std::is_same<O, numpy::functor::clip>::value &&
        !std::is_same<O, numpy::functor::where>::value &&
        // transtyping
        !std::is_same<O, numpy::functor::bool_>::value &&
        !std::is_same<O, numpy::functor::int8>::value &&
        !std::is_same<O, numpy::functor::int16>::value &&
        !std::is_same<O, numpy::functor::int32>::value &&
        !std::is_same<O, numpy::functor::int64>::value &&
        !std::is_same<O, numpy::functor::uint8>::value &&
        !std::is_same<O, numpy::functor::uint16>::value &&
        !std::is_same<O, numpy::functor::uint32>::value &&
        !std::is_same<O, numpy::functor::uint64>::value &&
        !std::is_same<O, numpy::functor::float32>::value &&
        !std::is_same<O, numpy::functor::float64>::value &&
        //
        true;
  };
}
PYTHONIC_NS_END

#endif
