#ifndef PYTHONIC_NUMPY_EXPR_H
#define PYTHONIC_NUMPY_EXPR_H

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/acos.hpp>
#include <nt2/include/functions/acosh.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/asinh.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/atanh.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/divfloor.hpp>
#include <nt2/include/functions/erf.hpp>
#include <nt2/include/functions/erfc.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/gamma.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/indeg.hpp>
#include <nt2/include/functions/inrad.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/mod.hpp>
#include <nt2/include/functions/nextafter.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/toolbox/boost_math/functions/lgamma.hpp>
#include <nt2/toolbox/boost_math/functions/tgamma.hpp>

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

            template<class T >
                auto reciprocal(T const& t) -> decltype(T(1)/t) {
                    return T(1)/t;
                }

            template<class T0, class T1>
                auto right_shift(T0 const& t0, T1 const& t1) -> decltype(t0 >> t1) {
                    return t0 >> t1;
                }

            template<class T0, class T1>
                auto minus(T0 const& t0, T1 const& t1) -> decltype(t0 - t1) {
                    return t0 - t1;
                }


        }
    }
    namespace core {

            PROXY(pythonic::numpy_expr::ops, minus)
#define NUMPY_BINARY_FUNC_NAME operator-
#define NUMPY_BINARY_FUNC_SYM proxy::minus
#include "numpy_binary_expr.h"


            PROXY(nt2, abs)
#define NUMPY_UNARY_FUNC_NAME absolute
#define NUMPY_UNARY_FUNC_SYM proxy::abs
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

            PROXY(pythonic::numpy_expr::ops, reciprocal)
#define NUMPY_UNARY_FUNC_NAME reciprocal
#define NUMPY_UNARY_FUNC_SYM proxy::reciprocal
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

            PROXY(nt2, sin)
#define NUMPY_UNARY_FUNC_NAME sin
#define NUMPY_UNARY_FUNC_SYM proxy::sin
#include "numpy_unary_expr.h"

            PROXY(nt2, tan)
#define NUMPY_UNARY_FUNC_NAME tan
#define NUMPY_UNARY_FUNC_SYM proxy::tan
#include "numpy_unary_expr.h"
    }
}

#endif
