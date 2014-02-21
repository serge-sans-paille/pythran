#ifndef PYTHONIC_TYPES_FLOAT_HPP
#define PYTHONIC_TYPES_FLOAT_HPP

#include <cmath>
#include "pythonic/types/attr.hpp"

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

namespace pythonic {
    namespace __builtin__ {
        template <size_t AttributeID>
            double getattr( double self) {
                return AttributeID == pythonic::types::attr::REAL ? self : 0.;
            }
    }
}

#endif
