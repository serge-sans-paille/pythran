#ifndef PYTHONIC_BUILTIN_LONG_HPP
#define PYTHONIC_BUILTIN_LONG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/long.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class T>
            pythran_long_t long_(T&& t) {
                return t;
            }
        pythran_long_t long_() {
            return 0;
        }
        PROXY(pythonic::__builtin__, long_);

    }

}

#endif

