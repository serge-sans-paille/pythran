#ifndef PYTHONIC_SLICE_H
#define PYTHONIC_SLICE_H

#include <limits>

namespace pythonic {
    namespace core {
        struct slice {
            long lower, upper, step;
            slice(long lower=0, long upper=std::numeric_limits<long>::max(), long step=1)
                : lower(lower), upper(upper), step(step) {}
        };
    }
}

#endif
