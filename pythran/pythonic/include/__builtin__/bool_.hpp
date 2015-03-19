#ifndef PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP
#define PYTHONIC_INCLUDE_BUILTIN_BOOL_HPP

#include "pythonic/utils/proxy.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

namespace pythonic {

    namespace __builtin__ {

        bool bool_();

        template<class T>
            bool bool_(T&& val);

#ifdef USE_GMP
        template<class T, class U>
            bool bool_(__gmp_expr<T,U> const& a);

        template<class T, class U>
            bool bool_(__gmp_expr<T,U> && a);
#endif

        PROXY_DECL(pythonic::__builtin__, bool_);
    }

}

#endif
