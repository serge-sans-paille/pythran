#ifndef PYTHONIC_NUMPY_EMPTY_HPP
#define PYTHONIC_NUMPY_EMPTY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<size_t N, class dtype=double>
            types::ndarray<typename types::numpy_type<dtype>::type, N> empty(types::array<long, N>const& shape, dtype d=dtype()) {
                return types::ndarray<typename types::numpy_type<dtype>::type, N>(shape, __builtin__::None);
            }
        template<class dtype=double>
            types::ndarray<dtype, 1> empty(long size, dtype d=dtype()) {
                return empty(types::make_tuple(size), d);
            }

        PROXY(pythonic::numpy, empty);

    }

}

#endif

