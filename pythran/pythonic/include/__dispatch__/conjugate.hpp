#ifndef PYTHONIC_INCLUDE_DISPATCH_CONJUGATE_HPP
#define PYTHONIC_INCLUDE_DISPATCH_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto conjugate(Any const& any)
            -> decltype(numpy::proxy::conjugate{}(any));

        PROXY_DECL(pythonic::__dispatch__, conjugate);

    }

}

#endif
