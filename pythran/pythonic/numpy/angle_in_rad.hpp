#ifndef PYTHONIC_NUMPY_ANGLEINRAD_HPP
#define PYTHONIC_NUMPY_ANGLEINRAD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/arctan.hpp"

namespace pythonic {

    namespace numpy {
        template<class T >
            auto angle_in_rad(T const& t) -> decltype(arctan(std::imag(t)/std::real(t))) {
                if(std::real(t)) return arctan(std::imag(t)/std::real(t));
                else return M_PI/2;
            }
        namespace wrapper {
            PROXY(pythonic::numpy, angle_in_rad)

        }
#define NUMPY_UNARY_FUNC_NAME angle_in_rad
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::angle_in_rad
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, angle_in_rad)

    }

}

#endif

