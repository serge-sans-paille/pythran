#ifndef PYTHONIC_NUMPY_ARRAY2STRING_HPP
#define PYTHONIC_NUMPY_ARRAY2STRING_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::str array2string(types::ndarray<T,N> const& a) {
                std::ostringstream oss;
                oss << a;
                return oss.str();
            }

        PROXY(pythonic::numpy, array2string);

    }

}

#endif

