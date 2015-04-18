#ifndef PYTHONIC_DISPATCH_CLEAR_HPP
#define PYTHONIC_DISPATCH_CLEAR_HPP

#include "pythonic/include/__dispatch__/clear.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {

        template<class Any>
            auto clear(Any&& any) -> decltype(any.clear());

        PROXY_IMPL(pythonic::__dispatch__, clear);

    }

}

#endif
