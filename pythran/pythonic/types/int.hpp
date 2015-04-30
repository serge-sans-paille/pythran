#ifndef PYTHONIC_TYPES_INT_HPP
#define PYTHONIC_TYPES_INT_HPP

#include "pythonic/include/types/int.hpp"

template <>
    long getattr<0>( long const & l)
    {
        return l;
    }

template <>
    long getattr<1>( long const & )
    {
        return 0L;
    }

#endif
