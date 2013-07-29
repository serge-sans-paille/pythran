#ifndef PYTHONIC_NDARRAY_FLATTEN_HPP
#define PYTHONIC_NDARRAY_FLATTEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace __ndarray__ {
        template<class T, size_t N>
            types::ndarray<T, 1>
            flatten(types::ndarray<T,N> const& a) {
                long n = a.size();
                T *buffer = new T[n];
                std::copy(a.buffer, a.buffer + n, buffer);
                long shape[1] = {n};
                return types::ndarray<T, 1>(buffer, shape);
            }

        PROXY(pythonic::__ndarray__, flatten);

    }

}

#endif

