#ifndef PYTHONIC_DISPATCH_UPDATE_HPP
#define PYTHONIC_DISPATCH_UPDATE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {

        template<class Any, class Arg0>
            auto update(Any&& any, Arg0 && arg0) -> decltype(any.update(std::forward<Arg0>(arg0))) {
                return any.update(std::forward<Arg0>(arg0));
            }
        template<class Any, class Arg0, class Arg1>
            auto update(Any&& any, Arg0 && arg0, Arg1 && arg1) -> decltype(any.update(std::forward<Arg0>(arg0), std::forward<Arg1>(arg1))) {
                return any.update(std::forward<Arg0>(arg0), std::forward<Arg1>(arg1));
            }

        PROXY(pythonic::__dispatch__, update);

    }

}

#endif
