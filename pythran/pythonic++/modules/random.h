#ifndef PYTHONIC_MODULE_RANDOM_H
#define PYTHONIC_MODULE_RANDOM_H
#include <cstdlib>
#include <random>

namespace pythonic {
    namespace random {

        static std::mt19937 __random_generator; 
        static __thread drand48_data __random_buffer;

        none_type seed(long s) { srand48_r(s, &__random_buffer); return None; }
        none_type seed() { srand48_r(time(nullptr), &__random_buffer); return None; }

        double random() { double v; drand48_r(&__random_buffer, &v); return v; }


        double gauss(double mu, double sigma) {
            return std::normal_distribution<>(mu, sigma)(__random_generator);
        }

        PROXY(pythonic::random, seed);
        PROXY(pythonic::random, random);
        PROXY(pythonic::random, gauss);
    }
}

#endif
