#ifndef PYTHONIC_OMP_IN_PARALLEL_HPP
#define PYTHONIC_OMP_IN_PARALLEL_HPP

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {
        auto in_parallel() -> decltype(omp_in_parallel()) {
            return omp_in_parallel();
        }
        PROXY(pythonic::omp, in_parallel);
    }

}

#endif
