#ifndef PYTHONIC_NUMPY_FLIPUD_HPP
#define PYTHONIC_NUMPY_FLIPUD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> flipud(types::ndarray<T,N> const& a) {
                types::ndarray<T,N> out(a.shape, __builtin__::None);
                std::reverse_copy(a.begin(), a.end(), out.begin());
                return out;
            }
        PROXY(pythonic::numpy, flipud);

    }

}

#endif

