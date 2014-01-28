#ifndef PYTHONIC_NUMPY_ISSCALAR_HPP
#define PYTHONIC_NUMPY_ISSCALAR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/types/str.hpp"

#include <type_traits>

namespace pythonic {

    namespace numpy {
        template<class E>
            constexpr bool isscalar(E const&) {
                return std::is_scalar<E>::value or types::is_complex<E>::value or std::is_same<E, types::str>::value;
            }
        PROXY(pythonic::numpy, isscalar);

    }

}

#endif

