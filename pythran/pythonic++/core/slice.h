#ifndef PYTHONIC_SLICE_H
#define PYTHONIC_SLICE_H

#include <limits>

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
// FIXME cross-reference
//                if(step==0)
//                    throw core::ValueError("slice step cannot be zero");
                long _lower, _upper, _step;
                if(step.is_none) _step = 1;
                else _step = step.data;
                if(upper.is_none and _step>0) _upper = max_size;
                else if(upper.is_none and _step<0) _upper = -1; 
                else if(upper.data<0) _upper = std::max((long)-1, max_size + upper);
                else if(upper.data> max_size) _upper = max_size;
                else _upper = upper.data;
                if(lower.is_none and _step>0) _lower = 0;
                else if(lower.is_none and _step<0) _lower = max_size - 1;
                else if(lower.data<0) _lower = std::max((long)0, max_size + lower);
                else if(lower.data > max_size) _lower= max_size - 1;
                else _lower = lower.data;
                return slice(_lower, _upper, _step);
            }

            void normalize_inplace(long max_size)
            {
//FIXME cross -reference
//                if(step==0)
//                    throw core::ValueError("slice step cannot be zero");
                if(step.is_none) step.data = 1;
                if(upper.is_none and step.data>0) upper.data = max_size;
                else if(upper.is_none and step.data<0) upper.data = -1; 
                else if(upper.data<0) upper.data = std::max((long)-1, max_size + upper.data);
                else if(upper.data> max_size) upper.data = max_size;
                if(lower.is_none and step.data>0) lower.data = 0;
                else if(lower.is_none and step.data<0) lower.data = max_size - 1;
                else if(lower.data<0) lower.data = std::max((long)0, max_size + lower.data);
                else if(lower.data > max_size) lower.data= max_size - 1;
            }

            long size() const
            {
                return std::max((long)0, (long)ceil(double(upper.data - lower.data)/step.data));
            }
        };
    }
}

#endif
