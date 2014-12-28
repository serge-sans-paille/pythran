#ifndef PYTHONIC_NUMPY_FLIPUD_HPP
#define PYTHONIC_NUMPY_FLIPUD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto flipud(E&& expr)
            -> decltype(std::forward<E>(expr)[types::slice{__builtin__::None, __builtin__::None, -1}])
            {
                return std::forward<E>(expr)[types::slice{__builtin__::None, __builtin__::None, -1}];
            }
        PROXY(pythonic::numpy, flipud);

    }

}

#endif

