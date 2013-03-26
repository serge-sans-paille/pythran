#ifndef PYTHONIC_NUMPY_EXPR_H
#define PYTHONIC_NUMPY_EXPR_H

namespace  pythonic {

    namespace core {
        namespace ops {
            struct plus {
                template<class T0, class T1>
                    auto operator()(T0 const& t0, T1 const& t1) const -> decltype(t0 + t1) {
                        return t0 + t1;
                    }
            };
            struct minus {
                template<class T0, class T1>
                    auto operator()(T0 const& t0, T1 const& t1) const -> decltype(t0 - t1) {
                        return t0 - t1;
                    }
            };

            struct negate {
                template<class T >
                    auto operator()(T const& t) const -> decltype(-t) {
                        return -t;
                    }
            };
        }

#define NUMPY_BINARY_FUNC_NAME operator+
#define NUMPY_BINARY_FUNC_SYM ops::plus
#include "numpy_binary_expr.h"

#define NUMPY_BINARY_FUNC_NAME operator-
#define NUMPY_BINARY_FUNC_SYM ops::minus
#include "numpy_binary_expr.h"

#define NUMPY_UNARY_FUNC_NAME operator-
#define NUMPY_UNARY_FUNC_SYM ops::negate
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME absolute
#define NUMPY_UNARY_FUNC_SYM pythonic::__builtin__::proxy::abs
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME arccos
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::acos
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME arccosh
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::acosh
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME arcsin
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::asin
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME arcsinh
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::asinh
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME arctan
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::atan
#include "numpy_unary_expr.h"

#define NUMPY_BINARY_FUNC_NAME arctan2
#define NUMPY_BINARY_FUNC_SYM pythonic::math::proxy::atan2
#include "numpy_binary_expr.h"

#define NUMPY_UNARY_FUNC_NAME arctanh
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::atanh
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME cos
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::cos
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME sin
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::sin
#include "numpy_unary_expr.h"

#define NUMPY_UNARY_FUNC_NAME tan
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::tan
#include "numpy_unary_expr.h"
    }
}

#endif
