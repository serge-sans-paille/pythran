#ifndef PYTHONIC_NUMPY_ONES_HPP
#define PYTHONIC_NUMPY_ONES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {

        template<size_t N, class dtype=double>
            types::ndarray<typename types::numpy_type<dtype>::type, N> ones(types::array<long, N> const& shape, dtype d=dtype()) {
                return types::ndarray<typename types::numpy_type<dtype>::type, N>(shape, typename types::numpy_type<dtype>::type(1));
            }

        template<class dtype=double>
            types::ndarray<typename types::numpy_type<dtype>::type, 1> ones(long size, dtype d=dtype()) {
                return ones(types::make_tuple(size), d);
            }

        PROXY(pythonic::numpy, ones);

    }

}

#endif

