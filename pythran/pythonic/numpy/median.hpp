#ifndef PYTHONIC_NUMPY_MEDIAN_HPP
#define PYTHONIC_NUMPY_MEDIAN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            decltype(std::declval<T>()+1.) median(types::ndarray<T,N> const& arr) {
                size_t n = arr.flat_size();
                T* tmp = new T[n];
                std::copy(arr.buffer, arr.buffer + n, tmp);
                std::sort(tmp, tmp + n);
                auto out = (tmp[n/2]+tmp[(n-1)/2])/double(2);
                delete [] tmp;
                return out;
            }
        template<class T, size_t N>
            decltype(std::declval<T>()+1.) median(types::ndarray<T,N> && arr) {
                size_t n = arr.flat_size();
                T* tmp = arr.buffer;
                std::sort(tmp, tmp + n);
                auto out = (tmp[n/2]+tmp[(n-1)/2])/double(2);
                return out;
            }

        NUMPY_EXPR_TO_NDARRAY0(median);

        PROXY(pythonic::numpy, median);

    }

}

#endif

