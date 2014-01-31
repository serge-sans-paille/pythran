#ifndef PYTHONIC_OMP_GET_NUM_THREADS_HPP
#define PYTHONIC_OMP_GET_NUM_THREADS_HPP

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {
        auto get_num_threads() -> decltype(omp_get_num_threads()) {
            return omp_get_num_threads();
        }
        PROXY(pythonic::omp, get_num_threads);
    }

}

#endif
