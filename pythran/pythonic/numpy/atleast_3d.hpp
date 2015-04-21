#ifndef PYTHONIC_NUMPY_ATLEAST3D_HPP
#define PYTHONIC_NUMPY_ATLEAST3D_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            typename std::enable_if<std::is_scalar<T>::value or types::is_complex<T>::value, types::ndarray<T,3>>::type
            atleast_3d(T t) {
                return types::ndarray<T,3>(types::make_tuple(1L,1L,1L), t);
            }
        template<class T>
            auto atleast_3d(T const& t)
            -> typename std::enable_if<
            not(std::is_scalar<T>::value or types::is_complex<T>::value) and (types::numpy_expr_to_ndarray<T>::type::value < 3),
            types::ndarray<typename types::numpy_expr_to_ndarray<T>::type::dtype, 3>
                > ::type
                {
                    auto r = asarray(t);
                    auto shape = r.shape();
                    if(shape.size() == 1)
                        return r.reshape(types::make_tuple(1L, shape[0],1L));
                    else
                        return r.reshape(types::make_tuple(shape[0], shape[1], 1L));
                }

        template<class T>
            auto atleast_3d(T const& t)
            -> typename std::enable_if<
            not(std::is_scalar<T>::value or types::is_complex<T>::value) and types::numpy_expr_to_ndarray<T>::type::value >= 3,
            decltype(asarray(t))
                > ::type
                {
                    return asarray(t);
                }

        PROXY(pythonic::numpy, atleast_3d);


    }

}

#endif

