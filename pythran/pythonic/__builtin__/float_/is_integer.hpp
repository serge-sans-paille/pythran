#ifndef PYTHONIC_BUILTIN_FLOAT_ISINTEGER_HPP
#define PYTHONIC_BUILTIN_FLOAT_ISINTEGER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/float_/is_integer.hpp"

#include <cmath>

namespace pythonic {

    namespace __builtin__ {

        namespace float_ {

            bool is_integer(double d)
            {
                double intpart;
                return std::modf(d, &intpart) == d;
            }

            PROXY_IMPL(pythonic::__builtin__::float_, is_integer);

        }
    }

}

#endif
