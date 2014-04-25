#ifndef PYTHONIC_NUMPY_MOD_HPP
#define PYTHONIC_NUMPY_MOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/mod.hpp"
#include "pythonic/types/assignable.hpp"

namespace pythonic {

    namespace operator_ {
        template<class A, class B>
            auto mod(A const& a, B const& b)
            -> typename std::enable_if<types::is_numexpr_arg<A>::value or types::is_numexpr_arg<B>::value,
                                       typename assignable<decltype(a%b)>::type>::type
            {
                auto t = a % b;
                t[t<0] = t[t<0] + b; // should be +=, but the patch is in parakeet-test-case
                return t;
            }
    }

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME mod
#define NUMPY_BINARY_FUNC_SYM operator_::mod
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

