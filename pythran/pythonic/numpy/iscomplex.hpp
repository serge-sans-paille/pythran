#ifndef PYTHONIC_NUMPY_ISCOMPLEX_HPP
#define PYTHONIC_NUMPY_ISCOMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class I>
                typename std::enable_if<types::is_complex<I>::value, bool>::type
                iscomplex(I const& a)
                {
                    return a.imag() != 0.;
                }

            template<class I>
                constexpr typename std::enable_if<not types::is_complex<I>::value, bool>::type
                iscomplex(I const& a)
                {
                    return false;
                }
        }

    #define NUMPY_UNARY_FUNC_NAME iscomplex
    #define NUMPY_UNARY_FUNC_SYM wrapper::iscomplex
    #include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

