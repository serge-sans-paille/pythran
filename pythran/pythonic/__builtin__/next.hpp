#ifndef PYTHONIC_BUILTIN_NEXT_HPP
#define PYTHONIC_BUILTIN_NEXT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/StopIteration.hpp"

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            typename std::remove_reference<decltype(*std::declval<T>())>::type next(T&& y) {
                if((decltype(y.begin()))y != y.end()) {
                    auto out = *y; ++y;
                    return out ;
                }
                else {
                    throw types::StopIteration("exhausted");
                }
            }
        PROXY(pythonic::__builtin__, next);

    }

}

#endif

