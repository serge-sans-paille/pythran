#ifndef PYTHONIC_INCLUDE_DISPATCH_REMOVE_HPP
#define PYTHONIC_INCLUDE_DISPATCH_REMOVE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any, class Arg0>
            auto remove(Any& any, Arg0 const & arg0)
            -> decltype(any.remove(arg0));

        PROXY_DECL(pythonic::__dispatch__, remove);

    }

}

#endif
