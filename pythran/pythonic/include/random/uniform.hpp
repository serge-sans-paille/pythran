#ifndef PYTHONIC_INCLUDE_RANDOM_UNIFORM_HPP
#define PYTHONIC_INCLUDE_RANDOM_UNIFORM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

namespace pythonic {

    namespace random {
        double uniform(double a, double b);

        PROXY_DECL(pythonic::random, uniform);


    }

}

#endif
