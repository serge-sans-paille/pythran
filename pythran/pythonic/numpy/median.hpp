#ifndef PYTHONIC_NUMPY_MEDIAN_HPP
#define PYTHONIC_NUMPY_MEDIAN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            decltype(std::declval<T>()+1.) median(types::ndarray<T,N> const& arr) {
                size_t n = arr.size();
                T* tmp = new T[n];
                std::copy(arr.buffer, arr.buffer + n, tmp);
                std::sort(tmp, tmp + n);
                auto out = (tmp[n/2]+tmp[(n-1)/2])/double(2);
                delete [] tmp;
                return out;
            }

        PROXY(pythonic::numpy, median);

    }

}

#endif

