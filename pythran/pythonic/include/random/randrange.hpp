#ifndef PYTHONIC_INCLUDE_RANDOM_RANDRANGE_HPP
#define PYTHONIC_INCLUDE_RANDOM_RANDRANGE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

#include <cmath>

namespace pythonic {

    namespace random {
        long randrange(long stop);
        long randrange(long start, long stop);
        long randrange(long start, long stop, long step);

        PROXY_DECL(pythonic::random, randrange)

    }

}

#endif
