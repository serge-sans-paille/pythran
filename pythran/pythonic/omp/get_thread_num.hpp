#ifndef PYTHONIC_OMP_GET_THREAD_NUM_HPP
#define PYTHONIC_OMP_GET_THREAD_NUM_HPP

#include "pythonic/include/omp/get_thread_num.hpp"

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {

        long get_thread_num()
        {
            return omp_get_thread_num();
        }

        PROXY_IMPL(pythonic::omp, get_thread_num);
    }

}

#endif
