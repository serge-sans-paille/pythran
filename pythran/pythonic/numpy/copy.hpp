#ifndef PYTHONIC_NUMPY_COPY_HPP
#define PYTHONIC_NUMPY_COPY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> copy(types::ndarray<T,N> const& a) {
                auto res = types::ndarray<T,N>(a.shape, __builtin__::None);
                std::copy(a.buffer, a.buffer + a.size(), res.buffer);
                return res;
            }
        NUMPY_EXPR_TO_NDARRAY0(copy);
        PROXY(pythonic::numpy, copy);

    }

}

#endif

