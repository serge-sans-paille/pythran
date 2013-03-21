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

#define NUMPY_UNARY_FUNC_NAME cos
#define NUMPY_UNARY_FUNC_SYM pythonic::math::proxy::cos
#include "numpy_unary_expr.h"

    }
}

#endif
