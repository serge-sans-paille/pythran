#ifndef PYTHONIC_INCLUDE_NUMPY_SWAPAXES_HPP
#define PYTHONIC_INCLUDE_NUMPY_SWAPAXES_HPP

#include "pythonic/numpy/transpose.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            auto swapaxes(T && a, int axis1, int axis2)
            -> decltype(_transpose(std::forward<T>(a),
                        std::declval<long [types::numpy_expr_to_ndarray<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::N]>()));

        PROXY_DECL(pythonic::numpy, swapaxes);

    }

}

#endif
