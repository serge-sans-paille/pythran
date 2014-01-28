#ifndef PYTHONIC_NUMPY_ARRAYSTR_HPP
#define PYTHONIC_NUMPY_ARRAYSTR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::str array_str(types::ndarray<T,N> const& a) {
                std::ostringstream oss;
                oss << a;
                return oss.str();
            }

        PROXY(pythonic::numpy, array_str);

    }

}

#endif

