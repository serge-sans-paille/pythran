#ifndef PYTHONIC_BUILTIN_ROUND_HPP
#define PYTHONIC_BUILTIN_ROUND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/pow.hpp"
#include "pythonic/include/__builtin__/round.hpp"

#include <cmath>

namespace pythonic {

    namespace __builtin__ {

        template <class T>
            double round(T const & v, size_t n)
            {
                T p = proxy::pow()(10, n);
                return std::lround(v * p) / p;
            }

        PROXY_IMPL(pythonic::__builtin__, round);

    }

}

#endif
