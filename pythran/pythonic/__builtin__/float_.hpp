#ifndef PYTHONIC_BUILTIN_FLOAT_HPP
#define PYTHONIC_BUILTIN_FLOAT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/float_.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif


namespace pythonic {

    namespace __builtin__ {

        template<class T>
            double float_(T&& t)
            {
                return t;
            }

        double float_()
        {
            return 0.f;
        }

#ifdef USE_GMP
        template<class T, class U>
            double float_(__gmp_expr<T,U> const& a)
            {
                return mpz_get_d(a.get_mpz_t());
            }
#endif

        PROXY_IMPL(pythonic::__builtin__, float_);

    }

}

#endif

