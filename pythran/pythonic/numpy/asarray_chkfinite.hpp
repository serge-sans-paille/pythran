#ifndef PYTHONIC_NUMPY_ASARRAYCHKFINITE_HPP
#define PYTHONIC_NUMPY_ASARRAYCHKFINITE_HPP

#include "pythonic/__builtin__/ValueError.hpp"
#include <nt2/include/functions/is_finite.hpp>

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class I>
                I asarray_chkfinite(I const& a)
                {
                    if(not nt2::is_finite(a))
                        throw types::ValueError("array must not contain infs or NaNs");
                    return a;
                }
        }

    #define NUMPY_UNARY_FUNC_NAME asarray_chkfinite
    #define NUMPY_UNARY_FUNC_SYM wrapper::asarray_chkfinite
    #include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

