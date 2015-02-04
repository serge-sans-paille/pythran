#ifndef PYTHONIC_NUMPY_ISREAL_HPP
#define PYTHONIC_NUMPY_ISREAL_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class I>
                typename std::enable_if<types::is_complex<I>::value, bool>::type
                isreal(I const& a)
                {
                    return a.imag() == 0.;
                }

            template<class I>
                typename std::enable_if<not types::is_complex<I>::value, bool>::type
                isreal(I const& a)
                {
                    return true;
                }
        }

#define NUMPY_NARY_FUNC_NAME isreal
#define NUMPY_NARY_FUNC_SYM wrapper::isreal
#include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

