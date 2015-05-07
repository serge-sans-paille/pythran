#ifndef PYTHONIC_INCLUDE_NUMPY_ATLEAST3D_HPP
#define PYTHONIC_INCLUDE_NUMPY_ATLEAST3D_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            typename std::enable_if<std::is_scalar<T>::value or types::is_complex<T>::value, types::ndarray<T,3>>::type
            atleast_3d(T t);

        template<class T>
            auto atleast_3d(T const& t)
            -> typename std::enable_if<
            not(std::is_scalar<T>::value or types::is_complex<T>::value) and (types::numpy_expr_to_ndarray<T>::type::value < 3),
            types::ndarray<typename types::numpy_expr_to_ndarray<T>::type::dtype, 3>
                > ::type;

        template<class T>
            auto atleast_3d(T const& t)
            -> typename std::enable_if<
            not(std::is_scalar<T>::value or types::is_complex<T>::value) and types::numpy_expr_to_ndarray<T>::type::value >= 3,
            decltype(asarray(t))
                > ::type;

        PROXY_DECL(pythonic::numpy, atleast_3d);

    }

}

#endif
