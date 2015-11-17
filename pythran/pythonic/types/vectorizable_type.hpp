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
    namespace proxy
    {
      struct mod;
    }
  }

  namespace numpy
  {
    namespace proxy
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
      struct round;
      struct round_;
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
          not std::is_same<O, numpy::proxy::mod>::value and
          not std::is_same<O, operator_::proxy::mod>::value and
          not std::is_same<O, numpy::proxy::logaddexp2>::value and
          // Return type for generic function should be generic
          not std::is_same<O, numpy::proxy::angle_in_rad>::value and
          not std::is_same<O, numpy::proxy::ldexp>::value and
          not std::is_same<O, numpy::proxy::isfinite>::value and
          not std::is_same<O, numpy::proxy::fix>::value and
          not std::is_same<O, numpy::proxy::isinf>::value and
          not std::is_same<O, numpy::proxy::isnan>::value and
          not std::is_same<O, numpy::proxy::isposinf>::value and
          not std::is_same<O, numpy::proxy::rint>::value and
          not std::is_same<O, numpy::proxy::round>::value and
          not std::is_same<O, numpy::proxy::round_>::value and
          not std::is_same<O, numpy::proxy::signbit>::value and
          // conditional processing doesn't permit SIMD
          not std::is_same<O, numpy::proxy::nan_to_num>::value and
          not std::is_same<O, numpy::proxy::asarray_chkfinite>::value and
          not std::is_same<O, numpy::proxy::clip>::value and
          not std::is_same<O, numpy::proxy::where>::value and
          // transtyping
          not std::is_same<O, numpy::proxy::int8>::value and
          not std::is_same<O, numpy::proxy::int16>::value and
          not std::is_same<O, numpy::proxy::int32>::value and
          not std::is_same<O, numpy::proxy::int64>::value and
          not std::is_same<O, numpy::proxy::uint8>::value and
          not std::is_same<O, numpy::proxy::uint16>::value and
          not std::is_same<O, numpy::proxy::uint32>::value and
          not std::is_same<O, numpy::proxy::uint64>::value and
          not std::is_same<O, numpy::proxy::float32>::value and
          not std::is_same<O, numpy::proxy::float64>::value and
          //
          true;
    };
  }
}

#endif
