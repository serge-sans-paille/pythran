#ifndef PYTHONIC_FLOAT_ISINTEGER_HPP
#define PYTHONIC_FLOAT_ISINTEGER_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {
namespace __builtin__ {

    namespace float_ {
        bool is_integer(double d) {
            double intpart;
            return std::modf(d, &intpart) == d;
        }
        PROXY(pythonic::__builtin__::float_, is_integer);

    }
}

}

#endif

