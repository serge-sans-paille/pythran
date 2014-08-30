#ifndef PYTHRAN_PYTHONIC_BUILTIN_POW_HPP
#define PYTHRAN_PYTHONIC_BUILTIN_POW_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/power.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class T, class U>
            pythran_long_t pow(__gmp_expr<T,U> const& a, long b) {
                mpz_class rop;
                mpz_pow_ui(rop.get_mpz_t(), a.get_mpz_t(), b);
                return rop;
            }
    }
}
#endif

namespace pythonic {

    namespace __builtin__ {

        template<class T0, class T1>
          auto pow(T0&& n, T1&& m) -> decltype(numpy::proxy::power{}(std::forward<T0>(n), std::forward<T1>(m)))
          {
            return numpy::proxy::power{}(std::forward<T0>(n), std::forward<T1>(m));
          }

        PROXY(pythonic::__builtin__, pow);

    }

}

#endif
