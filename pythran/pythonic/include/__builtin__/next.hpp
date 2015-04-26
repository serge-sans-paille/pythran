#ifndef PYTHONIC_INCLUDE_BUILTIN_NEXT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_NEXT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class T>
            typename std::remove_reference<decltype(*std::declval<T>())>::type
            next(T&& y);

        PROXY_DECL(pythonic::__builtin__, next);
    }

}

#endif
