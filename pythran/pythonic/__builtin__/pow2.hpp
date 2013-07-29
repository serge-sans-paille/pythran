#ifndef PYTHONIC_BUILTIN_POW2_HPP
#define PYTHONIC_BUILTIN_POW2_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class T>
            auto pow2(T const& e) -> decltype(e*e) { return e*e; }
        PROXY(pythonic::__builtin__, pow2);

    }

}

#endif

