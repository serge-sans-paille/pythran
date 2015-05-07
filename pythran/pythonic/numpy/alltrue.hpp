#ifndef PYTHONIC_NUMPY_ALLTRUE_HPP
#define PYTHONIC_NUMPY_ALLTRUE_HPP

#include "pythonic/include/numpy/alltrue.hpp"

#include "pythonic/numpy/all.hpp"

namespace pythonic {

    namespace numpy {
        template<class... Types>
            auto alltrue(Types&&... types) -> decltype(all(std::forward<Types>(types)...))
            {
                return all(std::forward<Types>(types)...);
            }

        PROXY_IMPL(pythonic::numpy, alltrue);

    }

}

#endif
