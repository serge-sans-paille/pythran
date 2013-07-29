#ifndef PYTHRAN_PYTHONIC_BUILTIN_POW_HPP
#define PYTHRAN_PYTHONIC_BUILTIN_POW_HPP

#include "pythonic/utils/proxy.hpp"

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

#include <cmath>
namespace pythonic {

    namespace __builtin__ {

        using std::pow;
        long pow(long n, long m) { return std::pow(n,m); }
        PROXY(pythonic::__builtin__, pow);

    }

}

#endif
