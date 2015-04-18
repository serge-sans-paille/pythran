#ifndef PYTHONIC_DISPATCH_REMOVE_HPP
#define PYTHONIC_DISPATCH_REMOVE_HPP

#include "pythonic/include/__dispatch__/remove.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any, class Arg0>
            auto remove(Any& any, Arg0 const & arg0)
            -> decltype(any.remove(arg0))
            {
                return any.remove(arg0);
            }

        PROXY_IMPL(pythonic::__dispatch__, remove);

    }

}

#endif
