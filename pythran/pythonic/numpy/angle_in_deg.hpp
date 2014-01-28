#ifndef PYTHONIC_NUMPY_ANGLEINDEG_HPP
#define PYTHONIC_NUMPY_ANGLEINDEG_HPP

#include "pythonic/numpy/angle_in_rad.hpp"
#include <nt2/include/functions/indeg.hpp>


namespace pythonic {

    namespace numpy {

        template<class T >
            auto angle_in_deg(T const& t) -> decltype(nt2::indeg(angle_in_rad(t))) {
                return nt2::indeg(angle_in_rad(t));
            }
        namespace wrapper {
            PROXY(pythonic::numpy, angle_in_deg)

        }
#define NUMPY_UNARY_FUNC_NAME angle_in_deg
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::angle_in_deg
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, angle_in_deg)

    }

}

#endif

