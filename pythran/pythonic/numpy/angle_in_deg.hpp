#ifndef PYTHONIC_NUMPY_ANGLEINDEG_HPP
#define PYTHONIC_NUMPY_ANGLEINDEG_HPP

#include "pythonic/numpy/angle_in_rad.hpp"
#include <nt2/include/functions/indeg.hpp>

/* NOTE: angle_in_deg is not part of the official Numpy API,
 * this file is here only to split the angle function in two parts
 */

namespace pythonic {

    namespace numpy {

        namespace wrapper {
            template<class T >
                auto angle_in_deg(T const& t) -> decltype(nt2::indeg(angle_in_rad(t))) {
                    return nt2::indeg(angle_in_rad(t));
                }
        }
#define NUMPY_UNARY_FUNC_NAME angle_in_deg
#define NUMPY_UNARY_FUNC_SYM wrapper::angle_in_deg
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

