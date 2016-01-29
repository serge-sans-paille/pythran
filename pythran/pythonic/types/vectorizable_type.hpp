#ifndef PYTHONIC_TYPES_VECTORIZABLE_TYPE_HPP
#define PYTHONIC_TYPES_VECTORIZABLE_TYPE_HPP

#include "pythonic/include/types/vectorizable_type.hpp"

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

namespace pythonic
{
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
      struct mod;
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
      // vectorization, and SG did not invest enough time in those
      static const bool value =
          not std::is_same<O, numpy::functor::mod>::value and
          not std::is_same<O, operator_::functor::mod>::value and
          not std::is_same<O, numpy::functor::logaddexp2>::value and
          // Return type for generic function should be generic
          not std::is_same<O, numpy::functor::angle_in_rad>::value and
          not std::is_same<O, numpy::functor::ldexp>::value and
          not std::is_same<O, numpy::functor::isfinite>::value and
          not std::is_same<O, numpy::functor::fix>::value and
          not std::is_same<O, numpy::functor::isinf>::value and
          not std::is_same<O, numpy::functor::isnan>::value and
          not std::is_same<O, numpy::functor::isposinf>::value and
          not std::is_same<O, numpy::functor::rint>::value and
          not std::is_same<O, numpy::functor::signbit>::value and
          // conditional processing doesn't permit SIMD
          not std::is_same<O, numpy::functor::nan_to_num>::value and
          not std::is_same<O, numpy::functor::asarray_chkfinite>::value and
          not std::is_same<O, numpy::functor::clip>::value and
          not std::is_same<O, numpy::functor::where>::value and
          // transtyping
          not std::is_same<O, numpy::functor::int8>::value and
          not std::is_same<O, numpy::functor::int16>::value and
          not std::is_same<O, numpy::functor::int32>::value and
          not std::is_same<O, numpy::functor::int64>::value and
          not std::is_same<O, numpy::functor::uint8>::value and
          not std::is_same<O, numpy::functor::uint16>::value and
          not std::is_same<O, numpy::functor::uint32>::value and
          not std::is_same<O, numpy::functor::uint64>::value and
          not std::is_same<O, numpy::functor::float32>::value and
          not std::is_same<O, numpy::functor::float64>::value and
          //
          true;
    };
  }
}

#endif
