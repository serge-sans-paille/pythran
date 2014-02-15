#ifndef PYTHONIC_OMP_GET_THREAD_NUM_HPP
#define PYTHONIC_OMP_GET_THREAD_NUM_HPP

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {
        auto get_thread_num() -> decltype(omp_get_thread_num()) {
            return omp_get_thread_num();
        }
        PROXY(pythonic::omp, get_thread_num);
    }

}

#endif
