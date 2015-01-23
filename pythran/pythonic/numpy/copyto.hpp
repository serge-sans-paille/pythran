#ifndef PYTHONIC_NUMPY_COPYTO_HPP
#define PYTHONIC_NUMPY_COPYTO_HPP
#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {
    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> copyto(types::ndarray<T,N>& out, types::ndarray<T,N> const& a) {
                std::copy(a.fbegin(), a.fend(), out.fbegin());
                return out;
            }
        PROXY(pythonic::numpy, copyto);
    }
}

#endif
