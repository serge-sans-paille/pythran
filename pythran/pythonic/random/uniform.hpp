#ifndef PYTHONIC_RANDOM_UNIFORM_HPP
#define PYTHONIC_RANDOM_UNIFORM_HPP

#include "pythonic/include/random/uniform.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

namespace pythonic {

    namespace random {
        double uniform(double a, double b)
        {
            return a + (b-a)*random();
        }

        PROXY_IMPL(pythonic::random, uniform);

    }

}

#endif
