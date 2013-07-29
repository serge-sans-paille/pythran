#ifndef PYTHONIC_RANDOM_RANDRANGE_HPP
#define PYTHONIC_RANDOM_RANDRANGE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

#include <cmath>

namespace pythonic {

    namespace random {
        long randrange(long stop) {
            return long(random() * stop);
        }

        long randrange(long start, long stop) {
            return start + long(random() * (stop - start));
        }

        long randrange(long start, long stop, long step) {
            return start + step * long((random() * (stop - start)) / std::abs(step));
        }
        PROXY(pythonic::random, randrange)

    }

}

#endif

