#ifndef PYTHONIC_DISPATCH_NEXT_HPP
#define PYTHONIC_DISPATCH_NEXT_HPP

#include "pythonic/include/__dispatch__/next.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {

        template<class Any>
            auto next(Any&& any) -> decltype(any.next())
            {
                return any.next();
            }

        PROXY_IMPL(pythonic::__dispatch__, next);

    }

}

#endif
