#ifndef PYTHONIC_TYPES_SLICE_HPP
#define PYTHONIC_TYPES_SLICE_HPP

#include "pythonic/__builtin__/None.hpp"

#include <cassert>


namespace pythonic {

    namespace types {

        struct normalized_slice {
            long lower, upper, step;
            normalized_slice() {}
            normalized_slice(long lower, long upper, long step = 1)
                : lower(lower), upper(upper), step(step) {}

            long size() const
            {
                return std::max(0L, long(ceil(double(upper - lower)/double(step))));
            }
        };

        struct slice {
            none<long> lower, upper, step;
            slice(none<long> lower, none<long> upper, none<long> step = 1)
                : lower(lower), upper(upper), step(step) {}
            slice(){}

            /*
               Normalize change a[:-1] to a[:len(a)-1] to have positif index.
               It also check for value bigger than len(a) to fit the size of the container
               */
            normalized_slice normalize(long max_size) const
            {
                long normalized_step = step.is_none ? 1L : (long)step;

                long normalized_upper;
                if(upper.is_none and normalized_step>0L) normalized_upper = max_size;
                else if(upper.is_none and normalized_step<0L) normalized_upper = -1L; 
                else if(upper<0L) normalized_upper = std::max(-1L, max_size + upper);
                else if(upper> max_size) normalized_upper = max_size;
                else normalized_upper = (long)upper;

                long normalized_lower = (long)lower;
                if(lower.is_none and normalized_step>0L) normalized_lower = 0L;
                else if(lower.is_none and normalized_step<0L) normalized_lower = max_size - 1L;
                else if(lower <0L) normalized_lower = std::max(0L, max_size + lower);
                else if(lower > max_size) normalized_lower = max_size - 1L;
                else normalized_lower = (long)lower;

                return normalized_slice(normalized_lower, normalized_upper, normalized_step);
            }

            long size() const
            {
                assert( not upper.is_none and not lower.is_none and not step.is_none );
                return std::max(0L, long(ceil(double(upper - lower)/double(step))));
            }
        };
    }
}

#endif
