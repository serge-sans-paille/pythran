#ifndef PYTHONIC_NUMPY_RANK_HPP
#define PYTHONIC_NUMPY_RANK_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            size_t rank(E const& expr)
            {
                return E::value;
            }

        PROXY(pythonic::numpy, rank);

    }

}

#endif

