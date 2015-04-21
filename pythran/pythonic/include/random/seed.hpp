#ifndef PYTHONIC_INCLUDE_RANDOM_SEED_HPP
#define PYTHONIC_INCLUDE_RANDOM_SEED_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/random/random.hpp"

#include <ctime>

namespace pythonic {

    namespace random {
        types::none_type seed(long s);
        types::none_type seed();

        PROXY_DECL(pythonic::random, seed);

    }

}

#endif
