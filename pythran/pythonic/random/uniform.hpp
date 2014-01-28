#ifndef PYTHONIC_RANDOM_UNIFORM_HPP
#define PYTHONIC_RANDOM_UNIFORM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

namespace pythonic {

    namespace random {
        double uniform(double a, double b) {
            return a + (b-a)*random();
        }
        PROXY(pythonic::random, uniform);


    }

}

#endif

