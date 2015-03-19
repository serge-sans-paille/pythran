#ifndef PYTHONIC_INCLUDE_BUILTIN_LONG_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LONG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/long.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class T>
            pythran_long_t long_(T&& t);

        pythran_long_t long_();

        PROXY_DECL(pythonic::__builtin__, long_);

    }

}

#endif
