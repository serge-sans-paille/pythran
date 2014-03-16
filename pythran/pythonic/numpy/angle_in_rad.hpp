#ifndef PYTHONIC_NUMPY_ANGLEINRAD_HPP
#define PYTHONIC_NUMPY_ANGLEINRAD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/arctan.hpp"

namespace pythonic {

    namespace numpy {
        namespace wrapper {
            template<class T >
                auto angle_in_rad(T const& t) -> decltype(nt2::atan(std::imag(t)/std::real(t))) {
                    if(std::real(t)) return nt2::atan(std::imag(t)/std::real(t));
                    else return M_PI/2;
                }
        }
#define NUMPY_UNARY_FUNC_NAME angle_in_rad
#define NUMPY_UNARY_FUNC_SYM wrapper::angle_in_rad
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

