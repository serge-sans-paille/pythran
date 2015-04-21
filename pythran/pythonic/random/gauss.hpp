#ifndef PYTHONIC_RANDOM_GAUSS_HPP
#define PYTHONIC_RANDOM_GAUSS_HPP

#include "pythonic/include/random/gauss.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/random/random.hpp"

namespace pythonic {

    namespace random {

        double gauss(double mu, double sigma)
        {
            return std::normal_distribution<>(mu, sigma)(__random_generator);
        }

        PROXY_IMPL(pythonic::random, gauss);

    }

}

#endif
