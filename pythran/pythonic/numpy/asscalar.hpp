#ifndef PYTHONIC_NUMPY_ASSCALAR_HPP
#define PYTHONIC_NUMPY_ASSCALAR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto asscalar(E const& expr) -> decltype(expr.at(0)) {
                if(expr.size() != 1)
                    throw types::ValueError("can only convert an array  of size 1 to a Python scalar");
                return expr.at(0);
            }

        PROXY(pythonic::numpy, asscalar);

    }

}

#endif

