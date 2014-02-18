#ifndef PYTHONIC_OMP_GET_WTIME_HPP
#define PYTHONIC_OMP_GET_WTIME_HPP

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {
        auto get_wtime() -> decltype(omp_get_wtime()) {
            return omp_get_wtime();
        }
        PROXY(pythonic::omp, get_wtime);
    }

}

#endif
