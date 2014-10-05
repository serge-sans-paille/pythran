#ifndef PYTHONIC_NUMPY_SWAPAXES_HPP
#define PYTHONIC_NUMPY_SWAPAXES_HPP

#include "pythonic/numpy/transpose.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            auto swapaxes(T && a, int axis1, int axis2)
            -> decltype(_transpose(std::forward<T>(a),
                        std::declval<long [types::numpy_expr_to_ndarray<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::N]>()))
            {
                constexpr long N = types::numpy_expr_to_ndarray<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::N;
                long t[N];
                for(unsigned long i = 0; i<N; ++i)
                    t[i] = i;
                std::swap(t[axis1], t[axis2]);
                return _transpose(std::forward<T>(a), t);
            }

        PROXY(pythonic::numpy, swapaxes);

    }

}

#endif

