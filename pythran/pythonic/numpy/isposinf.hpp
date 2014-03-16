#ifndef PYTHONIC_NUMPY_ISPOSINF_HPP
#define PYTHONIC_NUMPY_ISPOSINF_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_positive.hpp>

namespace pythonic {

    namespace numpy {
        namespace wrapper {
            template<class T>
                auto isposinf(T const& t) -> decltype(nt2::is_inf(t) and nt2::is_positive(t)) {
                    return nt2::is_inf(t) and nt2::is_positive(t);
                }
        }
#define NUMPY_UNARY_FUNC_NAME isposinf
#define NUMPY_UNARY_FUNC_SYM wrapper::isposinf
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

