#ifndef PYTHONIC_TYPES_NUMPY_OPERATORS_HPP
#define PYTHONIC_TYPES_NUMPY_OPERATORS_HPP

#include "pythonic/operator_/add.hpp"
#include "pythonic/operator_/and_.hpp"
#include "pythonic/operator_/inv.hpp"
#include "pythonic/operator_/or_.hpp"
#include "pythonic/operator_/__xor__.hpp"
#include "pythonic/operator_/div.hpp"
#include "pythonic/operator_/eq.hpp"
#include "pythonic/operator_/mod.hpp"
#include "pythonic/operator_/gt.hpp"
#include "pythonic/operator_/ge.hpp"
#include "pythonic/operator_/lshift.hpp"
#include "pythonic/operator_/lt.hpp"
#include "pythonic/operator_/le.hpp"
#include "pythonic/operator_/mul.hpp"
#include "pythonic/operator_/neg.hpp"
#include "pythonic/operator_/not_.hpp"
#include "pythonic/operator_/ne.hpp"
#include "pythonic/operator_/pos.hpp"
#include "pythonic/operator_/rshift.hpp"
#include "pythonic/operator_/sub.hpp"

namespace pythonic {
    /* operators must live in the same namespace as the associated type */
    namespace types {
#define NUMPY_BINARY_FUNC_NAME operator+
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::add
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator&
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::and_
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_UNARY_FUNC_NAME operator~
#define NUMPY_UNARY_FUNC_SYM operator_::proxy::invert
#include "pythonic/types/numpy_unary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator|
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::or_
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator^
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::__xor__
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator/
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::div
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator==
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::eq
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator%
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::mod
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator>
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::gt
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator>=
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::ge
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator<<
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::lshift
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator<
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::lt
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator<=
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::le
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator*
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::mul
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_UNARY_FUNC_NAME operator-
#define NUMPY_UNARY_FUNC_SYM operator_::proxy::neg
#include "pythonic/types/numpy_unary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator!=
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::ne
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_UNARY_FUNC_NAME operator+
#define NUMPY_UNARY_FUNC_SYM operator_::proxy::pos
#include "pythonic/types/numpy_unary_expr.hpp"

#define NUMPY_UNARY_FUNC_NAME operator!
#define NUMPY_UNARY_FUNC_SYM operator_::proxy::not_
#include "pythonic/types/numpy_unary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator>>
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::rshift
#include "pythonic/types/numpy_binary_expr.hpp"

#define NUMPY_BINARY_FUNC_NAME operator-
#define NUMPY_BINARY_FUNC_SYM operator_::proxy::sub
#include "pythonic/types/numpy_binary_expr.hpp"

    }
}

#endif
