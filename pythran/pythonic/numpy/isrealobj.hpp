#ifndef PYTHONIC_NUMPY_ISREALOBJ_HPP
#define PYTHONIC_NUMPY_ISREALOBJ_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/traits.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            constexpr bool isrealobj(E const& expr) {
                return not types::is_complex<typename types::numpy_expr_to_ndarray<E>::type::dtype>::value ;
            }

        PROXY(pythonic::numpy, isrealobj);

    }

}

#endif

