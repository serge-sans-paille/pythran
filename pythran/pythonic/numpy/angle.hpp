#ifndef PYTHONIC_NUMPY_ANGLE_HPP
#define PYTHONIC_NUMPY_ANGLE_HPP

#include "pythonic/numpy/angle_in_deg.hpp"
#include "pythonic/numpy/angle_in_rad.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            auto angle(T const& t, bool in_deg) -> decltype(typename types::numpy_expr_to_ndarray<T>::type(angle_in_rad(typename types::numpy_expr_to_ndarray<T>::type(t)))) {
                if(in_deg)
                    return typename types::numpy_expr_to_ndarray<T>::type(angle_in_deg(typename types::numpy_expr_to_ndarray<T>::type(t)));
                else
                    return typename types::numpy_expr_to_ndarray<T>::type(angle_in_rad(typename types::numpy_expr_to_ndarray<T>::type(t)));
            }
        template<class T>
            auto angle(T const& t) -> typename std::enable_if<not types::is_numpy_expr<T>::value,decltype(angle(t,false))>::type {
                return angle(t,false);
            }
        PROXY(pythonic::numpy, angle);

    }

}

#endif

