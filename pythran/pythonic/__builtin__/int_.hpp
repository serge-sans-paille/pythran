#ifndef PYTHONIC_BUILTIN_INT_HPP
#define PYTHONIC_BUILTIN_INT_HPP

#include "pythonic/utils/proxy.hpp"
#include <cassert>

namespace pythonic {

    namespace __builtin__ {

        template<class T>
            long int_(T&& t) {
                return t;
            }

        long int_(char t) {
            assert( t >= '0' and t <= '9' );
            return t - '0';
        }

        PROXY(pythonic::__builtin__, int_);

    }

}

#endif

