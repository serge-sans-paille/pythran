#ifndef PYTHONIC_NUMPY_NANTONUM_HPP
#define PYTHONIC_NUMPY_NANTONUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <limits>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_positive.hpp>

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class I>
                I nan_to_num(I const& a)
                {
                    if(nt2::is_inf(a)) {
                        if(nt2::is_positive(a))
                            return std::numeric_limits<I>::max();
                        else
                            return std::numeric_limits<I>::lowest();
                    }
                    else if(nt2::is_nan(a))
                        return 0;
                    else
                        return a;
                }
        }

    #define NUMPY_UNARY_FUNC_NAME nan_to_num
    #define NUMPY_UNARY_FUNC_SYM wrapper::nan_to_num
    #include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

