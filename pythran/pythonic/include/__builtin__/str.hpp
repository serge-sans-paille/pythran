#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_HPP

#include "pythonic/types/str.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        namespace anonymous {
            template <class T>
                types::str str(T&& t);

            inline types::str str(long value);
            inline types::str str(double l);
        }

        PROXY_DECL(pythonic::__builtin__::anonymous, str);
    }

}

#endif
