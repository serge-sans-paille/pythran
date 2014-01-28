#ifndef PYTHONIC_NUMPY_NAN_HPP
#define PYTHONIC_NUMPY_NAN_HPP

#include <limits>

namespace pythonic {

    namespace numpy {
        double const nan = std::numeric_limits<double>::quiet_NaN();

    }

}

#endif

