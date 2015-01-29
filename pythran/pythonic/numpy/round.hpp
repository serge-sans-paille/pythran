#ifndef PYTHONIC_NUMPY_ROUND_HPP
#define PYTHONIC_NUMPY_ROUND_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/iround2even.hpp>

namespace pythonic {

    namespace numpy {
        namespace wrapper {
            template<class T>
                T round(T const& v)
                {
                    return nt2::iround2even(v);
                }
        }
#define NUMPY_NARY_FUNC_NAME round
#define NUMPY_NARY_FUNC_SYM wrapper::round
#include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

