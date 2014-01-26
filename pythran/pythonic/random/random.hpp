#ifndef PYTHONIC_RANDOM_RANDOM_HPP
#define PYTHONIC_RANDOM_RANDOM_HPP

#include "pythonic/utils/proxy.hpp"
#include <random>

namespace pythonic {

    namespace random {

        static std::mt19937 __random_generator;

        double random() {
            static std::uniform_real_distribution<> uniform_distrib(0.0, 1.0);
            return uniform_distrib(__random_generator);
        }

        PROXY(pythonic::random, random);

    }

}

#endif

