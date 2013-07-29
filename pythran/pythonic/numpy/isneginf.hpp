#ifndef PYTHONIC_NUMPY_ISNEGINF_HPP
#define PYTHONIC_NUMPY_ISNEGINF_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_negative.hpp>

namespace pythonic {

    namespace numpy {
        template<class T>
            auto isneginf(T const& t) -> decltype(nt2::is_inf(t) and nt2::is_negative(t)) {
                return nt2::is_inf(t) and nt2::is_negative(t);
            }
        namespace wrapper {
            PROXY(pythonic::numpy, isneginf)

        }
#define NUMPY_UNARY_FUNC_NAME isneginf
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::isneginf
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, isneginf)

    }

}

#endif

