#ifndef PYTHONIC_NDARRAY_FLATTEN_HPP
#define PYTHONIC_NDARRAY_FLATTEN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic { namespace numpy  {

    namespace ndarray {
        template<class T, size_t N>
            auto flatten(types::ndarray<T,N> const& a)
            -> decltype(a.flat())
            {
                return a.flat();
            }

        NUMPY_EXPR_TO_NDARRAY0(flatten);
        PROXY(pythonic::numpy::ndarray, flatten);

    }

}

}
#endif

