#ifndef PYTHONIC_OMP_SET_NESTED_HPP
#define PYTHONIC_OMP_SET_NESTED_HPP

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {
        template<class T>
        auto set_nested(T&& val) -> decltype(omp_set_nested(std::forward<T>(val))) {
            return omp_set_nested(std::forward<T>(val));
        }
        PROXY(pythonic::omp, set_nested);
    }

}

#endif
