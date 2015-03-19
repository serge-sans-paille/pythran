#ifndef PYTHONIC_INCLUDE_BUILTIN_POW_HPP
#define PYTHONIC_INCLUDE_BUILTIN_POW_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/power.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

namespace pythonic {

    namespace __builtin__ {

        template<class T0, class T1>
          auto pow(T0&& n, T1&& m)
          -> decltype(numpy::proxy::power{}(std::forward<T0>(n), std::forward<T1>(m)));

#ifdef USE_GMP
        template<class T, class U>
            pythran_long_t pow(__gmp_expr<T,U> const& a, long b);
#endif

        PROXY_DECL(pythonic::__builtin__, pow);

    }

}

#endif
