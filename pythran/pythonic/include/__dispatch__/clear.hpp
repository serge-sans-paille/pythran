#ifndef PYTHONIC_INCLUDE_DISPATCH_CLEAR_HPP
#define PYTHONIC_INCLUDE_DISPATCH_CLEAR_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto clear(Any&& any) -> decltype(any.clear())
            {
                return any.clear();
            }

        PROXY_DECL(pythonic::__dispatch__, clear);

    }

}

#endif
