#ifndef PYTHONIC_RANDOM_RANDINT_HPP
#define PYTHONIC_RANDOM_RANDINT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/randrange.hpp"

namespace pythonic {

    namespace random {
        long randint(long a, long b) {
            return randrange(a, b+1);
        }
        PROXY(pythonic::random, randint);

    }

}

#endif

