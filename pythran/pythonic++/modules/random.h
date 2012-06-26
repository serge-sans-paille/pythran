#ifndef PYTHONIC_MODULE_RANDOM_H
#define PYTHONIC_MODULE_RANDOM_H
#include <cstdlib>

namespace pythonic {
    namespace random {
        none_type seed(long s) { srand48(s);}
        none_type seed() { srand48(time(nullptr));}

        double random() { return drand48(); }

        PROXY(pythonic::random, seed);
        PROXY(pythonic::random, random);
    }
}

#endif
