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

        double uniform(double a, double b) {
            return a + (b-a)*random();
        }

        double expovariate(double l) {
            return std::exponential_distribution<>(l)(__random_generator);
        }

        template<class Iterable>
            core::list<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::iterator::value_type>
            sample(Iterable&& s, size_t k) {
                typedef typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::iterator::value_type value_type;
                core::list<value_type> tmp(s);
                std::vector<size_t> indices(tmp.size());
                std::iota(indices.begin(), indices.end(), 0);
                std::random_shuffle(indices.begin(), indices.end());
                core::list<value_type> out(k);
                for(size_t i=0; i<k; i++)
                    out[i] = tmp[ indices[i] ];
                return out;
            }

        PROXY(pythonic::random, seed);
        PROXY(pythonic::random, random);
        PROXY(pythonic::random, gauss);
        PROXY(pythonic::random, uniform);
        PROXY(pythonic::random, expovariate);
        PROXY(pythonic::random, sample);
    }
}

#endif
