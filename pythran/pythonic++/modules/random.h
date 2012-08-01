#ifndef PYTHONIC_MODULE_RANDOM_H
#define PYTHONIC_MODULE_RANDOM_H
#include <cstdlib>
#include <random>

namespace pythonic {
    namespace random {

        static std::mt19937 __random_generator; 

        none_type seed(long s) { srand48(s); return None; }
        none_type seed() { srand48(time(nullptr)); return None; }

        double random() { return drand48(); }


        double gauss(double mu, double sigma) {
            return std::normal_distribution<>(mu, sigma)(__random_generator);
        }

        PROXY(pythonic::random, seed);
        PROXY(pythonic::random, random);
        PROXY(pythonic::random, gauss);
    }
}

#endif
