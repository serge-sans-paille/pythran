#ifndef PYTHONIC_OMP_IN_PARALLEL_HPP
#define PYTHONIC_OMP_IN_PARALLEL_HPP

#include "pythonic/include/omp/in_parallel.hpp"

#include <omp.h>
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace omp {

        bool in_parallel()
        {
            return omp_in_parallel();
        }

        PROXY_IMPL(pythonic::omp, in_parallel);
    }

}

#endif
