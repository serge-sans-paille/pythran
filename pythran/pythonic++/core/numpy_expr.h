#ifndef PYTHONIC_NUMPY_EXPR_H
#define PYTHONIC_NUMPY_EXPR_H

#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/acos.hpp>
#include <nt2/include/functions/scalar/acosh.hpp>
#include <nt2/include/functions/scalar/asin.hpp>
#include <nt2/include/functions/scalar/asinh.hpp>
#include <nt2/include/functions/scalar/atan.hpp>
#include <nt2/include/functions/scalar/atan2.hpp>
#include <nt2/include/functions/scalar/atanh.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/ceil.hpp>
#include <nt2/include/functions/scalar/conj.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/cos.hpp>
#include <nt2/include/functions/scalar/cosh.hpp>
#include <nt2/include/functions/scalar/divfloor.hpp>
#include <nt2/include/functions/scalar/eps.hpp>
#include <nt2/include/functions/scalar/erf.hpp>
#include <nt2/include/functions/scalar/erfc.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/expm1.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/frexp.hpp>
#include <nt2/include/functions/scalar/gamma.hpp>
#include <nt2/include/functions/scalar/hypot.hpp>
#include <nt2/include/functions/scalar/indeg.hpp>
#include <nt2/include/functions/scalar/inrad.hpp>
#include <nt2/include/functions/scalar/iround.hpp>
#include <nt2/include/functions/scalar/is_finite.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/ldexp.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/log10.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/log2.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/scalar/min.hpp>
#include <nt2/include/functions/scalar/mod.hpp>
#include <nt2/include/functions/scalar/nextafter.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/remainder.hpp>
#include <nt2/include/functions/scalar/sign.hpp>
#include <nt2/include/functions/scalar/sin.hpp>
#include <nt2/include/functions/scalar/sinh.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/tan.hpp>
#include <nt2/include/functions/scalar/tanh.hpp>
#include <nt2/include/functions/scalar/trunc.hpp>
#include <nt2/toolbox/boost_math/functions/lgamma.hpp>
#include <nt2/toolbox/boost_math/functions/tgamma.hpp>
#ifdef __AVX__
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/acos.hpp>
#include <nt2/include/functions/simd/acosh.hpp>
#include <nt2/include/functions/simd/asin.hpp>
#include <nt2/include/functions/simd/asinh.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/functions/simd/atan2.hpp>
#include <nt2/include/functions/simd/atanh.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/ceil.hpp>
#include <nt2/include/functions/simd/conj.hpp>
#include <nt2/include/functions/simd/copysign.hpp>
#include <nt2/include/functions/simd/cos.hpp>
#include <nt2/include/functions/simd/cosh.hpp>
#include <nt2/include/functions/simd/divfloor.hpp>
#include <nt2/include/functions/simd/eps.hpp>
#include <nt2/include/functions/simd/erf.hpp>
#include <nt2/include/functions/simd/erfc.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/frexp.hpp>
#include <nt2/include/functions/simd/gamma.hpp>
#include <nt2/include/functions/simd/hypot.hpp>
#include <nt2/include/functions/simd/indeg.hpp>
#include <nt2/include/functions/simd/inrad.hpp>
#include <nt2/include/functions/simd/iround.hpp>
#include <nt2/include/functions/simd/is_finite.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/log10.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functions/simd/log2.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/mod.hpp>
#include <nt2/include/functions/simd/nextafter.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/remainder.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functions/simd/sinh.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/tan.hpp>
#include <nt2/include/functions/simd/tanh.hpp>
#include <nt2/include/functions/simd/trunc.hpp>
#endif

namespace  pythonic {

    namespace numpy_expr {

        namespace ops {
            template<class T0, class T1>
                auto add(T0 const& t0, T1 const& t1) -> decltype(t0 + t1) {
                    return t0 + t1;
                }

            template<class T0, class T1>
                auto bitwise_and(T0 const& t0, T1 const& t1) -> decltype(t0 & t1) {
                    return t0 & t1;
                }

            template<class T0>
                decltype(~std::declval<T0>()) bitwise_not(T0 const& t0) {
                    return ~t0 ;
                }

            template<class T0, class T1>
                auto bitwise_or(T0 const& t0, T1 const& t1) -> decltype(t0 | t1) {
                    return t0 | t1;
                }

            template<class T0, class T1>
                auto bitwise_xor(T0 const& t0, T1 const& t1) -> decltype(t0 ^ t1) {
                    return t0 ^ t1;
                }

            template<class T0, class T1>
                auto divide(T0 const& t0, T1 const& t1) -> decltype(t0 / t1) {
                    return t0 / t1;
                }

            template<class T0, class T1>
                auto equal(T0 const& t0, T1 const& t1) -> decltype(t0 == t1) {
                    return t0 == t1;
                }

            template<class T>
                auto empty_like(T const&) -> decltype(T(0))/* prevents instanciation on a ndarray*/ {
                    return T();
                }

            template<class T0, class T1>
                auto greater(T0 const& t0, T1 const& t1) -> decltype(t0 > t1) {
                    return t0 > t1;
                }

            template<class T0, class T1>
                auto greater_equal(T0 const& t0, T1 const& t1) -> decltype(t0 >= t1) {
                    return t0 >= t1;
                }

            template<class T0, class T1>
                auto left_shift(T0 const& t0, T1 const& t1) -> decltype(t0 << t1) {
                    return t0 << t1;
                }

            template<class T0, class T1>
                auto less(T0 const& t0, T1 const& t1) -> decltype(t0 < t1) {
                    return t0 < t1;
                }

            template<class T0, class T1>
                auto less_equal(T0 const& t0, T1 const& t1) -> decltype(t0 <= t1) {
                    return t0 <= t1;
                }

            template<class T0, class T1>
                auto logaddexp(T0 const& t0, T1 const& t1) -> decltype(nt2::log(nt2::exp(t0) + nt2::exp(t1))) {
                    return nt2::log(nt2::exp(t0) + nt2::exp(t1));
                }

            template<class T0, class T1>
                auto logaddexp2(T0 const& t0, T1 const& t1) -> decltype(nt2::log2(nt2::pow(T0(2),t0) + nt2::pow(T1(2),t1))) {
                    return nt2::log2(nt2::pow(T0(2),t0) + nt2::pow(T1(2),t1));
                }

            template<class T0, class T1>
                auto logical_and(T0 const& t0, T1 const& t1) -> decltype(t0 and t1) {
                    return t0 and t1;
                }

            template<class T>
                auto logical_not(T const& t) -> decltype(not t) {
                    return not t;
                }

            template<class T0, class T1>
                auto logical_or(T0 const& t0, T1 const& t1) -> decltype(t0 or t1) {
                    return t0 or t1;
                }

            template<class T0, class T1>
                auto logical_xor(T0 const& t0, T1 const& t1) -> decltype((t0 and not t1) or (t1 and not t0)) {
                    return (t0 and not t1) or (t1 and not t0);
                }

            template<class T0, class T1>
                auto multiply(T0 const& t0, T1 const& t1) -> decltype(t0 * t1) {
                    return t0 * t1;
                }

            template<class T >
                auto negative(T const& t) -> decltype(-t) {
                    return -t;
                }

            template<class T0, class T1>
                auto not_equal(T0 const& t0, T1 const& t1) -> decltype(t0 != t1) {
                    return t0 != t1;
                }

            template<class T>
                auto ones_like(T const&) -> decltype(T(1)) {
                    return T(1);
                }

            template<class T >
                auto positive(T const& t) -> decltype(+t) {
                    return +t;
                }

            template<class T0, class T1>
                auto right_shift(T0 const& t0, T1 const& t1) -> decltype(t0 >> t1) {
                    return t0 >> t1;
                }
            template<class T>
                auto square(T const& t) -> decltype(t*t) {
                    return t*t;
                }

            template<class T0, class T1>
                auto subtract(T0 const& t0, T1 const& t1) -> decltype(t0 - t1) {
                    return t0 - t1;
                }

            template<class T>
                auto zeros_like(T const&) -> decltype(T(0)) {
                    return T(0);
                }

            template<class T >
                auto angle_in_rad(T const& t) -> decltype(atan(std::imag(t)/std::real(t))) {
                    if(std::real(t)) return atan(std::imag(t)/std::real(t));
                    else return M_PI/2;
                }

            template<class T >
                auto angle_in_deg(T const& t) -> decltype(nt2::indeg(angle_in_rad(t))) {
                    return nt2::indeg(angle_in_rad(t));
                }


        }
    }
    namespace core {

            PROXY(nt2, abs)
#define NUMPY_UNARY_FUNC_NAME abs
#define NUMPY_UNARY_FUNC_SYM proxy::abs
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME absolute
#define NUMPY_UNARY_FUNC_SYM proxy::abs
#include "numpy_unary_expr.h"

        PROXY(pythonic::numpy_expr::ops, angle_in_rad)
#define NUMPY_UNARY_FUNC_NAME angle_in_rad
#define NUMPY_UNARY_FUNC_SYM proxy::angle_in_rad
#include "numpy_unary_expr.h"

        PROXY(pythonic::numpy_expr::ops, angle_in_deg)
#define NUMPY_UNARY_FUNC_NAME angle_in_deg
#define NUMPY_UNARY_FUNC_SYM proxy::angle_in_deg
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, add)
#define NUMPY_BINARY_FUNC_NAME operator+
#define NUMPY_BINARY_FUNC_SYM proxy::add
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME add
#define NUMPY_BINARY_FUNC_SYM proxy::add
#include "numpy_binary_expr.h"

            PROXY(nt2, acos)
#define NUMPY_UNARY_FUNC_NAME arccos
#define NUMPY_UNARY_FUNC_SYM proxy::acos
#include "numpy_unary_expr.h"

            PROXY(nt2, acosh)
#define NUMPY_UNARY_FUNC_NAME arccosh
#define NUMPY_UNARY_FUNC_SYM proxy::acosh
#include "numpy_unary_expr.h"

            PROXY(nt2, asin)
#define NUMPY_UNARY_FUNC_NAME arcsin
#define NUMPY_UNARY_FUNC_SYM proxy::asin
#include "numpy_unary_expr.h"

            PROXY(nt2, asinh)
#define NUMPY_UNARY_FUNC_NAME arcsinh
#define NUMPY_UNARY_FUNC_SYM proxy::asinh
#include "numpy_unary_expr.h"

            PROXY(nt2, atan)
#define NUMPY_UNARY_FUNC_NAME arctan
#define NUMPY_UNARY_FUNC_SYM proxy::atan
#include "numpy_unary_expr.h"

            PROXY(nt2, atan2)
#define NUMPY_BINARY_FUNC_NAME arctan2
#define NUMPY_BINARY_FUNC_SYM proxy::atan2
#include "numpy_binary_expr.h"

            PROXY(nt2, atanh)
#define NUMPY_UNARY_FUNC_NAME arctanh
#define NUMPY_UNARY_FUNC_SYM proxy::atanh
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_and)
#define NUMPY_BINARY_FUNC_NAME operator&
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_and
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME bitwise_and
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_and
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_not)
#define NUMPY_UNARY_FUNC_NAME operator~
#define NUMPY_UNARY_FUNC_SYM proxy::bitwise_not
#include "numpy_unary_expr.h"
#define NUMPY_UNARY_FUNC_NAME bitwise_not
#define NUMPY_UNARY_FUNC_SYM proxy::bitwise_not
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_or)
#define NUMPY_BINARY_FUNC_NAME operator|
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_or
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME bitwise_or
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_or
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_xor)
#define NUMPY_BINARY_FUNC_NAME operator^
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_xor
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME bitwise_xor
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_xor
#include "numpy_binary_expr.h"

            PROXY(nt2, ceil)
#define NUMPY_UNARY_FUNC_NAME ceil
#define NUMPY_UNARY_FUNC_SYM proxy::ceil
#include "numpy_unary_expr.h"

            PROXY(nt2, copysign)
#define NUMPY_BINARY_FUNC_NAME copysign
#define NUMPY_BINARY_FUNC_SYM proxy::copysign
#include "numpy_binary_expr.h"

            PROXY(nt2, conj)
#define NUMPY_UNARY_FUNC_NAME conj
#define NUMPY_UNARY_FUNC_SYM proxy::conj
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME conjugate
#define NUMPY_UNARY_FUNC_SYM proxy::conj
#include "numpy_unary_expr.h"

            PROXY(nt2, cos)
#define NUMPY_UNARY_FUNC_NAME cos
#define NUMPY_UNARY_FUNC_SYM proxy::cos
#include "numpy_unary_expr.h"

            PROXY(nt2, cosh)
#define NUMPY_UNARY_FUNC_NAME cosh
#define NUMPY_UNARY_FUNC_SYM proxy::cosh
#include "numpy_unary_expr.h"

            PROXY(nt2, inrad)
#define NUMPY_UNARY_FUNC_NAME deg2rad
#define NUMPY_UNARY_FUNC_SYM proxy::inrad
#include "numpy_unary_expr.h"

            PROXY(nt2, indeg)
#define NUMPY_UNARY_FUNC_NAME degrees
#define NUMPY_UNARY_FUNC_SYM proxy::indeg
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, divide)
#define NUMPY_BINARY_FUNC_NAME operator/
#define NUMPY_BINARY_FUNC_SYM proxy::divide
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME divide
#define NUMPY_BINARY_FUNC_SYM proxy::divide
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, equal)
#define NUMPY_BINARY_FUNC_NAME operator==
#define NUMPY_BINARY_FUNC_SYM proxy::equal
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME equal
#define NUMPY_BINARY_FUNC_SYM proxy::equal
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, empty_like)
#define NUMPY_UNARY_FUNC_NAME empty_like
#define NUMPY_UNARY_FUNC_SYM proxy::empty_like
#include "numpy_unary_expr.h"

            PROXY(nt2, exp)
#define NUMPY_UNARY_FUNC_NAME exp
#define NUMPY_UNARY_FUNC_SYM proxy::exp
#include "numpy_unary_expr.h"

            PROXY(nt2, expm1)
#define NUMPY_UNARY_FUNC_NAME expm1
#define NUMPY_UNARY_FUNC_SYM proxy::expm1
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME fabs
#define NUMPY_UNARY_FUNC_SYM proxy::abs
#include "numpy_unary_expr.h"

            PROXY(nt2, floor)
#define NUMPY_UNARY_FUNC_NAME floor
#define NUMPY_UNARY_FUNC_SYM proxy::floor
#include "numpy_unary_expr.h"

            PROXY(nt2, divfloor)
#define NUMPY_BINARY_FUNC_NAME floor_divide
#define NUMPY_BINARY_FUNC_SYM proxy::divfloor
#include "numpy_binary_expr.h"

            PROXY(nt2, max)
#define NUMPY_BINARY_FUNC_NAME fmax
#define NUMPY_BINARY_FUNC_SYM proxy::max
#include "numpy_binary_expr.h"

            PROXY(nt2, min)
#define NUMPY_BINARY_FUNC_NAME fmin
#define NUMPY_BINARY_FUNC_SYM proxy::min
#include "numpy_binary_expr.h"

            PROXY(nt2, mod)
#define NUMPY_BINARY_FUNC_NAME operator%
#define NUMPY_BINARY_FUNC_SYM proxy::mod
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME fmod
#define NUMPY_BINARY_FUNC_SYM proxy::mod
#include "numpy_binary_expr.h"
// TODO
//            PROXY(nt2, frexp)
//#define NUMPY_UNARY_FUNC_NAME frexp
//#define NUMPY_UNARY_FUNC_SYM proxy::frexp
//#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, greater)
#define NUMPY_BINARY_FUNC_NAME operator>
#define NUMPY_BINARY_FUNC_SYM proxy::greater
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME greater
#define NUMPY_BINARY_FUNC_SYM proxy::greater
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, greater_equal)
#define NUMPY_BINARY_FUNC_NAME operator>=
#define NUMPY_BINARY_FUNC_SYM proxy::greater_equal
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME greater_equal
#define NUMPY_BINARY_FUNC_SYM proxy::greater_equal
#include "numpy_binary_expr.h"

            PROXY(nt2, hypot)
#define NUMPY_BINARY_FUNC_NAME hypot
#define NUMPY_BINARY_FUNC_SYM proxy::hypot
#include "numpy_binary_expr.h"

#define NUMPY_UNARY_FUNC_NAME invert
#define NUMPY_UNARY_FUNC_SYM proxy::bitwise_not
#include "numpy_unary_expr.h"

            PROXY(nt2, is_finite)
#define NUMPY_UNARY_FUNC_NAME isfinite
#define NUMPY_UNARY_FUNC_SYM proxy::is_finite
#include "numpy_unary_expr.h"

            PROXY(nt2, is_inf)
#define NUMPY_UNARY_FUNC_NAME isinf
#define NUMPY_UNARY_FUNC_SYM proxy::is_inf
#include "numpy_unary_expr.h"

            PROXY(nt2, is_nan)
#define NUMPY_UNARY_FUNC_NAME isnan
#define NUMPY_UNARY_FUNC_SYM proxy::is_nan
#include "numpy_unary_expr.h"

            PROXY(nt2, ldexp)
#define NUMPY_BINARY_FUNC_NAME ldexp
#define NUMPY_BINARY_FUNC_SYM proxy::ldexp
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, left_shift)
#define NUMPY_BINARY_FUNC_NAME operator<<
#define NUMPY_BINARY_FUNC_SYM proxy::left_shift
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME left_shift
#define NUMPY_BINARY_FUNC_SYM proxy::left_shift
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, less)
#define NUMPY_BINARY_FUNC_NAME operator<
#define NUMPY_BINARY_FUNC_SYM proxy::less
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME less
#define NUMPY_BINARY_FUNC_SYM proxy::less
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, less_equal)
#define NUMPY_BINARY_FUNC_NAME operator<=
#define NUMPY_BINARY_FUNC_SYM proxy::less_equal
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME less_equal
#define NUMPY_BINARY_FUNC_SYM proxy::less_equal
#include "numpy_binary_expr.h"

            PROXY(nt2, log)
#define NUMPY_UNARY_FUNC_NAME log
#define NUMPY_UNARY_FUNC_SYM proxy::log
#include "numpy_unary_expr.h"

            PROXY(nt2, log10)
#define NUMPY_UNARY_FUNC_NAME log10
#define NUMPY_UNARY_FUNC_SYM proxy::log10
#include "numpy_unary_expr.h"

            PROXY(nt2, log1p)
#define NUMPY_UNARY_FUNC_NAME log1p
#define NUMPY_UNARY_FUNC_SYM proxy::log1p
#include "numpy_unary_expr.h"

            PROXY(nt2, log2)
#define NUMPY_UNARY_FUNC_NAME log2
#define NUMPY_UNARY_FUNC_SYM proxy::log2
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, logaddexp)
#define NUMPY_BINARY_FUNC_NAME logaddexp
#define NUMPY_BINARY_FUNC_SYM proxy::logaddexp
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, logaddexp2)
#define NUMPY_BINARY_FUNC_NAME logaddexp2
#define NUMPY_BINARY_FUNC_SYM proxy::logaddexp2
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, logical_and)
#define NUMPY_BINARY_FUNC_NAME operator&&
#define NUMPY_BINARY_FUNC_SYM proxy::logical_and
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME logical_and
#define NUMPY_BINARY_FUNC_SYM proxy::logical_and
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, logical_not)
#define NUMPY_UNARY_FUNC_NAME logical_not
#define NUMPY_UNARY_FUNC_SYM proxy::logical_not
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, logical_or)
#define NUMPY_BINARY_FUNC_NAME operator||
#define NUMPY_BINARY_FUNC_SYM proxy::logical_or
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME logical_or
#define NUMPY_BINARY_FUNC_SYM proxy::logical_or
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, logical_xor)
#define NUMPY_BINARY_FUNC_NAME logical_xor
#define NUMPY_BINARY_FUNC_SYM proxy::logical_xor
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME maximum
#define NUMPY_BINARY_FUNC_SYM proxy::max
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME minimum
#define NUMPY_BINARY_FUNC_SYM proxy::max
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME mod
#define NUMPY_BINARY_FUNC_SYM proxy::mod
#include "numpy_binary_expr.h"

            // TODO modf

        PROXY(pythonic::numpy_expr::ops, multiply)
#define NUMPY_BINARY_FUNC_NAME operator*
#define NUMPY_BINARY_FUNC_SYM proxy::multiply
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME multiply
#define NUMPY_BINARY_FUNC_SYM proxy::multiply
#include "numpy_binary_expr.h"

        PROXY(pythonic::numpy_expr::ops, negative)
#define NUMPY_UNARY_FUNC_NAME operator-
#define NUMPY_UNARY_FUNC_SYM proxy::negative
#include "numpy_unary_expr.h"
#define NUMPY_UNARY_FUNC_NAME negative
#define NUMPY_UNARY_FUNC_SYM proxy::negative
#include "numpy_unary_expr.h"

            PROXY(nt2, nextafter)
#define NUMPY_BINARY_FUNC_NAME nextafter
#define NUMPY_BINARY_FUNC_SYM proxy::nextafter
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, not_equal)
#define NUMPY_BINARY_FUNC_NAME operator!=
#define NUMPY_BINARY_FUNC_SYM proxy::not_equal
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME not_equal
#define NUMPY_BINARY_FUNC_SYM proxy::not_equal
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, ones_like)
#define NUMPY_UNARY_FUNC_NAME ones_like
#define NUMPY_UNARY_FUNC_SYM proxy::ones_like
#include "numpy_unary_expr.h"

        PROXY(pythonic::numpy_expr::ops, positive)
#define NUMPY_UNARY_FUNC_NAME operator+
#define NUMPY_UNARY_FUNC_SYM proxy::positive
#include "numpy_unary_expr.h"

            PROXY(nt2, pow)
#define NUMPY_BINARY_FUNC_NAME power
#define NUMPY_BINARY_FUNC_SYM proxy::pow
#include "numpy_binary_expr.h"

#define NUMPY_UNARY_FUNC_NAME rad2deg
#define NUMPY_UNARY_FUNC_SYM proxy::indeg
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME radians
#define NUMPY_UNARY_FUNC_SYM proxy::inrad
#include "numpy_unary_expr.h"

            PROXY(nt2, rec)
#define NUMPY_UNARY_FUNC_NAME reciprocal
#define NUMPY_UNARY_FUNC_SYM proxy::rec
#include "numpy_unary_expr.h"

            PROXY(nt2, remainder)
#define NUMPY_BINARY_FUNC_NAME remainder
#define NUMPY_BINARY_FUNC_SYM proxy::remainder
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, right_shift)
#define NUMPY_BINARY_FUNC_NAME operator>>
#define NUMPY_BINARY_FUNC_SYM proxy::right_shift
#include "numpy_binary_expr.h"
#define NUMPY_BINARY_FUNC_NAME right_shift
#define NUMPY_BINARY_FUNC_SYM proxy::right_shift
#include "numpy_binary_expr.h"

            PROXY(nt2, iround)
#define NUMPY_UNARY_FUNC_NAME rint
#define NUMPY_UNARY_FUNC_SYM proxy::iround
#include "numpy_unary_expr.h"

            PROXY(nt2, sign)
#define NUMPY_UNARY_FUNC_NAME sign
#define NUMPY_UNARY_FUNC_SYM proxy::sign
#include "numpy_unary_expr.h"

            PROXY(nt2, bitofsign)
#define NUMPY_UNARY_FUNC_NAME signbit
#define NUMPY_UNARY_FUNC_SYM proxy::bitofsign
#include "numpy_unary_expr.h"

            PROXY(nt2, sin)
#define NUMPY_UNARY_FUNC_NAME sin
#define NUMPY_UNARY_FUNC_SYM proxy::sin
#include "numpy_unary_expr.h"

            PROXY(nt2, sinh)
#define NUMPY_UNARY_FUNC_NAME sinh
#define NUMPY_UNARY_FUNC_SYM proxy::sinh
#include "numpy_unary_expr.h"

            PROXY(nt2, eps)
#define NUMPY_UNARY_FUNC_NAME spacing
#define NUMPY_UNARY_FUNC_SYM proxy::eps
#include "numpy_unary_expr.h"

            PROXY(nt2, sqrt)
#define NUMPY_UNARY_FUNC_NAME sqrt
#define NUMPY_UNARY_FUNC_SYM proxy::sqrt
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, square)
#define NUMPY_UNARY_FUNC_NAME square
#define NUMPY_UNARY_FUNC_SYM proxy::sqrt
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, subtract)
#define NUMPY_BINARY_FUNC_NAME operator-
#define NUMPY_BINARY_FUNC_SYM proxy::subtract
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME subtract
#define NUMPY_BINARY_FUNC_SYM proxy::subtract
#include "numpy_binary_expr.h"


            PROXY(nt2, tan)
#define NUMPY_UNARY_FUNC_NAME tan
#define NUMPY_UNARY_FUNC_SYM proxy::tan
#include "numpy_unary_expr.h"

            PROXY(nt2, tanh);
#define NUMPY_UNARY_FUNC_NAME tanh
#define NUMPY_UNARY_FUNC_SYM proxy::tanh
#include "numpy_unary_expr.h"

            PROXY(nt2, trunc);
#define NUMPY_UNARY_FUNC_NAME trunc
#define NUMPY_UNARY_FUNC_SYM proxy::trunc
#include "numpy_unary_expr.h"

            // SG: badd
#define NUMPY_BINARY_FUNC_NAME true_divide
#define NUMPY_BINARY_FUNC_SYM proxy::divide
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, zeros_like)
#define NUMPY_UNARY_FUNC_NAME zeros_like
#define NUMPY_UNARY_FUNC_SYM proxy::zeros_like
#include "numpy_unary_expr.h"

    }
}

#endif
