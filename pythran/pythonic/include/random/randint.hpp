#ifndef PYTHONIC_INCLUDE_RANDOM_RANDINT_HPP
#define PYTHONIC_INCLUDE_RANDOM_RANDINT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/randrange.hpp"

namespace pythonic {

    namespace random {

        long randint(long a, long b);

        PROXY_DECL(pythonic::random, randint);

    }

}

#endif
