#ifndef PYTHONIC_INCLUDE_NUMPY_ARGSORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARGSORT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<long, N> argsort(types::ndarray<T,N> const& a);

        NUMPY_EXPR_TO_NDARRAY0_DECL(argsort);

        PROXY_DECL(pythonic::numpy, argsort);

    }

}

#endif
