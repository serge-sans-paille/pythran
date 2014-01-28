#ifndef PYTHONIC_TYPES_INT_HPP
#define PYTHONIC_TYPES_INT_HPP

#include <cmath>

namespace pythonic {

    inline long mod(long d, long l) {
        return d % l;
    }
    inline long floordiv(long a, long b) {
        return floor(static_cast<double>(a)/b);
    }

}

template <int I> long getattr( long const & );
template <> long getattr<0>( long const & l) { return l;}
template <> long getattr<1>( long const & ) { return 0L;}

#endif
