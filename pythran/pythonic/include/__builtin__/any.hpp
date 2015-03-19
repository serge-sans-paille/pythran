#ifndef PYTHONIC_INCLUDE_BUILTIN_ANY_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ANY_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__  {
        template <class Iterable>
            bool any(Iterable && s);

        PROXY_DECL(pythonic::__builtin__, any);

    }

}

#endif
