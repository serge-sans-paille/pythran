#ifndef PYTHONIC_DISPATCH_NEXT_HPP
#define PYTHONIC_DISPATCH_NEXT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/exceptions.hpp"

namespace pythonic {

    namespace __dispatch__ {
#if 0
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
#endif
        template<class Any>
            auto next(Any&& any) -> decltype(any.next()) {return any.next();}
        PROXY(pythonic::__dispatch__, next);

    }

}

#endif

