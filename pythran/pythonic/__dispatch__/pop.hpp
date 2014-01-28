#ifndef PYTHONIC_DISPATCH_POP_HPP
#define PYTHONIC_DISPATCH_POP_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto pop(Any&& any)
            -> decltype(any.pop())
            {
                return any.pop();
            }
        template<class Any, class Arg0>
            auto pop(Any&& any, Arg0 && arg0)
            -> decltype(any.pop(std::forward<Arg0>(arg0)))
            {
                return any.pop(std::forward<Arg0>(arg0));
            }
        template<class Any, class Arg0, class Arg1>
            auto pop(Any&& any, Arg0 && arg0, Arg1 && arg1)
            -> decltype(any.pop(std::forward<Arg0>(arg0),std::forward<Arg1>(arg1)))
            {
                return any.pop(std::forward<Arg0>(arg0),std::forward<Arg1>(arg1));
            }
        PROXY(pythonic::__dispatch__, pop);

    }

}

#endif

