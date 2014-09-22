#ifndef PYTHONIC_NUMPY_ZEROS_HPP
#define PYTHONIC_NUMPY_ZEROS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<size_t N, class dtype=double>
            types::ndarray<typename types::numpy_type<dtype>::type, N> zeros(types::array<long, N> const& shape, dtype d=dtype()) {
              typedef typename types::numpy_type<dtype>::type T;
              // use calloc even if we have a non integer type. This looks ok on modern architecture, although not really standard
              T* buffer = (T*)calloc(std::accumulate(shape.begin(), shape.end(), 1L, std::multiplies<long>()), sizeof(T));
              return types::ndarray<T, N>{buffer, shape.data()};
            }

        template<class dtype=double>
            types::ndarray<typename types::numpy_type<dtype>::type, 1> zeros(long size, dtype d=dtype()) {
                return zeros(types::make_tuple(size), d);
            }


        PROXY(pythonic::numpy, zeros);

    }

}

#endif

