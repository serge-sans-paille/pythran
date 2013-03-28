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
#include <nt2/include/functions/erf.hpp>
#include <nt2/include/functions/erfc.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/gamma.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/indeg.hpp>
#include <nt2/include/functions/inrad.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/mod.hpp>
#include <nt2/include/functions/pow.hpp>
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
                auto multiply(T0 const& t0, T1 const& t1) -> decltype(t0 * t1) {
                    return t0 * t1;
                }

            template<class T0, class T1>
                auto minus(T0 const& t0, T1 const& t1) -> decltype(t0 - t1) {
                    return t0 - t1;
                }

            template<class T >
                auto negate(T const& t) -> decltype(-t) {
                    return -t;
                }


        }
    }
    namespace core {
        PROXY(pythonic::numpy_expr::ops, multiply)
#define NUMPY_BINARY_FUNC_NAME operator*
#define NUMPY_BINARY_FUNC_SYM proxy::multiply
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, minus)
#define NUMPY_BINARY_FUNC_NAME operator-
#define NUMPY_BINARY_FUNC_SYM proxy::minus
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, negate)
#define NUMPY_UNARY_FUNC_NAME operator-
#define NUMPY_UNARY_FUNC_SYM proxy::negate
#include "numpy_unary_expr.h"

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
#define NUMPY_BINARY_FUNC_NAME bitwise_and
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_and
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_not)
#define NUMPY_UNARY_FUNC_NAME bitwise_not
#define NUMPY_UNARY_FUNC_SYM proxy::bitwise_not
#include "numpy_unary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_or)
#define NUMPY_BINARY_FUNC_NAME bitwise_or
#define NUMPY_BINARY_FUNC_SYM proxy::bitwise_or
#include "numpy_binary_expr.h"

            PROXY(pythonic::numpy_expr::ops, bitwise_xor)
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

            PROXY(nt2, hypot)
#define NUMPY_BINARY_FUNC_NAME hypot
#define NUMPY_BINARY_FUNC_SYM proxy::hypot
#include "numpy_binary_expr.h"

            PROXY(nt2, is_inf)
#define NUMPY_UNARY_FUNC_NAME isinf
#define NUMPY_UNARY_FUNC_SYM proxy::is_inf
#include "numpy_unary_expr.h"

            PROXY(nt2, is_nan)
#define NUMPY_UNARY_FUNC_NAME isnan
#define NUMPY_UNARY_FUNC_SYM proxy::is_nan
#include "numpy_unary_expr.h"

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
