#ifndef PYTHONIC_OMP_GET_WTICK_HPP
#define PYTHONIC_OMP_GET_WTICK_HPP

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {
        auto get_wtick() -> decltype(omp_get_wtick()) {
            return omp_get_wtick();
        }
        PROXY(pythonic::omp, get_wtick);
    }

}

#endif
