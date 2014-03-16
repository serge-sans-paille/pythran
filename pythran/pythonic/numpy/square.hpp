#ifndef PYTHONIC_NUMPY_SQUARE_HPP
#define PYTHONIC_NUMPY_SQUARE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class T>
                auto square(T const& t) -> typename std::enable_if<std::is_scalar<T>::value, decltype(t*t)>::type
                {
                    return t*t;
                }
        }

#define NUMPY_UNARY_FUNC_NAME square
#define NUMPY_UNARY_FUNC_SYM wrapper::square
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

