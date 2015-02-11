#ifndef PYTHONIC_NUMPY_ARRAYEQUAL_HPP
#define PYTHONIC_NUMPY_ARRAYEQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/all.hpp"

namespace pythonic {

    namespace numpy {
        template<class U, class V>
            bool array_equal(U const& u, V const&v) {
                if(u.shape() == v.shape()) {
                    return all(types::numpy_expr<operator_::proxy::eq, U, V>(u, v));
                }
                return false;
            }

        PROXY(pythonic::numpy, array_equal);

    }

}

#endif

