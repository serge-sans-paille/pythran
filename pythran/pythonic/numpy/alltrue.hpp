#ifndef PYTHONIC_NUMPY_ALLTRUE_HPP
#define PYTHONIC_NUMPY_ALLTRUE_HPP

#include "pythonic/numpy/all.hpp"

namespace pythonic {

    namespace numpy {
        template<class... Types>
            auto alltrue(Types&&... types) -> decltype(all(std::forward<Types>(types)...)) {
                return all(std::forward<Types>(types)...);
            }

        PROXY(pythonic::numpy, alltrue);

    }

}

#endif

