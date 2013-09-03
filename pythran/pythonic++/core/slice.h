#ifndef PYTHONIC_SLICE_H
#define PYTHONIC_SLICE_H

#include <limits>
#include <cassert>

namespace pythonic {
    namespace core {
        struct slice {
            none<long> lower, upper, step;
            slice(none<long> lower, none<long> upper, none<long> step = 1)
                : lower(lower), upper(upper), step(step) {}
            slice(){}

            /*
                Normalize change a[:-1] to a[:len(a)-1] to have positif index.
                It also check for value bigger than len(a) to fit the size of the container
            */
            slice normalize(long max_size) const
            {
                slice out(*this);
                out.normalize_inplace(max_size);
                return out;
            }

            void normalize_inplace(long max_size)
            {
//                if(step==0)
//                    throw core::ValueError("slice step cannot be zero");
                if(step.is_none) step = 1L;

                if(upper.is_none and step>0L) upper = max_size;
                else if(upper.is_none and step<0L) upper = -1L; 
                else if(upper<0L) upper = std::max(-1L, max_size + upper);
                else if(upper> max_size) upper = max_size;

                if(lower.is_none and step>0L) lower = 0L;
                else if(lower.is_none and step<0L) lower = max_size - 1L;
                else if(lower <0L) lower = std::max(0L, max_size + lower);
                else if(lower > max_size) lower = max_size - 1L;
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
