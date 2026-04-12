#ifndef PYTHONIC_TYPES_VECTORIZABLE_TYPE_HPP
#define PYTHONIC_TYPES_VECTORIZABLE_TYPE_HPP

#include "pythonic/include/types/vectorizable_type.hpp"

#include "pythonic/numpy/bool_.hpp"
#include "pythonic/numpy/float32.hpp"
#include "pythonic/numpy/float64.hpp"
#include "pythonic/numpy/int16.hpp"
#include "pythonic/numpy/int32.hpp"
#include "pythonic/numpy/int64.hpp"
#include "pythonic/numpy/int8.hpp"
#include "pythonic/numpy/uint16.hpp"
#include "pythonic/numpy/uint32.hpp"
#include "pythonic/numpy/uint64.hpp"
#include "pythonic/numpy/uint8.hpp"
#include "pythonic/types/traits.hpp"

PYTHONIC_NS_BEGIN
namespace operator_
{
  namespace functor
  {
    struct mod;
    struct div;
  } // namespace functor
} // namespace operator_

namespace builtins
{
  namespace pythran
  {
    namespace functor
    {
      struct abssqr;
    }
  } // namespace pythran
} // namespace builtins

namespace numpy
{
  namespace functor
  {
    struct arctan2;
    struct angle_in_rad;
    struct asarray_chkfinite;
    struct clip;
    struct copysign;
    struct divide;
    struct fix;
    struct floor_divide;
    struct fmod;
    struct heaviside;
    struct hypot;
    struct isfinite;
    struct isinf;
    struct isnan;
    struct isposinf;
    struct ldexp;
    struct logaddexp;
    struct logaddexp2;
    struct maximum;
    struct minimum;
    struct nan_to_num;
    struct nextafter;
    struct power;
    struct remainder;
    struct rint;
    struct signbit;
    struct spacing;
    struct true_divide;
    struct where;
  } // namespace functor
} // namespace numpy
namespace scipy
{
  namespace special
  {
    namespace functor
    {
      struct binom;
      struct gammaincinv;
      struct hankel1;
      struct hankel2;
      struct jv;
      struct i0;
      struct i0e;
      struct iv;
      struct kv;
      struct yv;
      struct jvp;
      struct ivp;
      struct kvp;
      struct yvp;
      struct ndtr;
      struct ndtri;
      struct spherical_jn;
      struct spherical_yn;
    } // namespace functor
  } // namespace special
} // namespace scipy
namespace types
{
  template <class O, class... Args>
  struct is_vector_op {

    // vectorize everything but these ops. They require special handling for
    // vectorization, and SG did not invest enough time in those
    static const bool value =
        !std::is_same_v<O, operator_::functor::mod> &&
        (!std::is_same_v<O, operator_::functor::div> ||
         (std::is_same_v<Args, decltype(std::declval<O>()(std::declval<Args>()...))> && ...)) &&
        !std::is_same_v<O, numpy::functor::logaddexp2> &&
        // Return type for generic function should be generic
        !std::is_same_v<O, numpy::functor::angle_in_rad> &&
        !std::is_same_v<O, numpy::functor::ldexp> && !std::is_same_v<O, numpy::functor::isfinite> &&
        !std::is_same_v<O, numpy::functor::fix> && !std::is_same_v<O, numpy::functor::isinf> &&
        !std::is_same_v<O, numpy::functor::isnan> && !std::is_same_v<O, numpy::functor::isposinf> &&
        !std::is_same_v<O, numpy::functor::rint> && !std::is_same_v<O, numpy::functor::signbit> &&
        // conditional processing doesn't permit SIMD
        !std::is_same_v<O, numpy::functor::nan_to_num> &&
        !std::is_same_v<O, numpy::functor::asarray_chkfinite> &&
        !std::is_same_v<O, numpy::functor::clip> && !std::is_same_v<O, numpy::functor::where> &&
        // not supported by xsimd
        !std::is_same_v<O, numpy::functor::nextafter> &&
        !std::is_same_v<O, numpy::functor::spacing> &&
        // not supported for complex numbers
        !((is_complex<typename dtype_of<Args>::type>::value || ...) &&
          (std::is_same_v<O, numpy::functor::floor_divide> ||
           std::is_same_v<O, numpy::functor::maximum> ||
           std::is_same_v<O, builtins::pythran::functor::abssqr> ||
           std::is_same_v<O, numpy::functor::minimum>)) &&
        // transtyping
        !std::is_same_v<O, numpy::functor::bool_> && !std::is_same_v<O, numpy::functor::int8> &&
        !std::is_same_v<O, numpy::functor::int16> && !std::is_same_v<O, numpy::functor::int32> &&
        !std::is_same_v<O, numpy::functor::int64> && !std::is_same_v<O, numpy::functor::uint8> &&
        !std::is_same_v<O, numpy::functor::uint16> && !std::is_same_v<O, numpy::functor::uint32> &&
        !std::is_same_v<O, numpy::functor::uint64> && !std::is_same_v<O, numpy::functor::float32> &&
        !std::is_same_v<O, numpy::functor::float64> &&
        // not supported for integral numbers
        !((std::is_integral_v<typename dtype_of<Args>::type> || ...) &&
          (std::is_same_v<O, numpy::functor::floor_divide> ||
           std::is_same_v<O, numpy::functor::true_divide> ||
           std::is_same_v<O, numpy::functor::divide> ||
           std::is_same_v<O, numpy::functor::arctan2> ||
           std::is_same_v<O, numpy::functor::copysign> ||
           std::is_same_v<O, numpy::functor::logaddexp> ||
           std::is_same_v<O, numpy::functor::power> ||
           std::is_same_v<O, numpy::functor::remainder> ||
           std::is_same_v<O, numpy::functor::hypot> || std::is_same_v<O, numpy::functor::fmod>)) &&
        // special functions not in the scope of xsimd
        !std::is_same_v<O, numpy::functor::heaviside> &&
        !std::is_same_v<O, scipy::special::functor::binom> &&
        !std::is_same_v<O, scipy::special::functor::gammaincinv> &&
        !std::is_same_v<O, scipy::special::functor::hankel1> &&
        !std::is_same_v<O, scipy::special::functor::hankel2> &&
        !std::is_same_v<O, scipy::special::functor::jv> &&
        !std::is_same_v<O, scipy::special::functor::i0> &&
        !std::is_same_v<O, scipy::special::functor::i0e> &&
        !std::is_same_v<O, scipy::special::functor::iv> &&
        !std::is_same_v<O, scipy::special::functor::kv> &&
        !std::is_same_v<O, scipy::special::functor::yv> &&
        !std::is_same_v<O, scipy::special::functor::jvp> &&
        !std::is_same_v<O, scipy::special::functor::ivp> &&
        !std::is_same_v<O, scipy::special::functor::kvp> &&
        !std::is_same_v<O, scipy::special::functor::ndtr> &&
        !std::is_same_v<O, scipy::special::functor::ndtri> &&
        !std::is_same_v<O, scipy::special::functor::yvp> &&
        !std::is_same_v<O, scipy::special::functor::spherical_jn> &&
        !std::is_same_v<O, scipy::special::functor::spherical_yn> &&
        //
        true;
  };
} // namespace types
PYTHONIC_NS_END

#endif
