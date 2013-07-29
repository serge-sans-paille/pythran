#ifndef PYTHONIC_TYPES_FLOAT_HPP
#define PYTHONIC_TYPES_FLOAT_HPP

#include <cmath>

namespace pythonic {

    inline double mod(double d, long l) {
        return fmod(d,double(l));
    }

    inline long floordiv(double a, long b) {
        return floor(a/b);
    }

    inline long floordiv(long a, double b) {
        return floor(a/b);
    }

    inline long floordiv(double a, double b) {
        return floor(a/b);
    }
}

#endif
