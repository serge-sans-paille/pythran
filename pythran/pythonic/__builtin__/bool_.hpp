#ifndef PYTHONIC_BUILTIN_BOOL_HPP
#define PYTHONIC_BUILTIN_BOOL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/bool.hpp"

#ifdef USE_GMP
#include "pythonic/types/long.hpp"

namespace pythonic {

    namespace __builtin__ {
        template<class T, class U>
            bool bool_(__gmp_expr<T,U> const& a) {
                return a != 0;
            }
        template<class T, class U>
            bool bool_(__gmp_expr<T,U> && a) {
                return a != 0;
            }
    }
}
#endif

namespace pythonic {

    namespace __builtin__ {
        template<class T>
            bool bool_(T&& val) { return (bool)val; }

        bool bool_() { return false; }

        PROXY(pythonic::__builtin__, bool_);
    }

}

#endif

