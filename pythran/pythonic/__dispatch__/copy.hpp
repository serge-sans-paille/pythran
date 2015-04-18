#ifndef PYTHONIC_DISPATCH_COPY_HPP
#define PYTHONIC_DISPATCH_COPY_HPP

#include "pythonic/include/__dispatch__/copy.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto copy(Any const& any) -> decltype(any.copy())
            {
                return any.copy();
            }

        PROXY_IMPL(pythonic::__dispatch__, copy);

    }

}

#endif
