#ifndef PYTHONIC_DISPATCH_CONJUGATE_HPP
#define PYTHONIC_DISPATCH_CONJUGATE_HPP

#include "pythonic/include/__dispatch__/conjugate.hpp"
#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto conjugate(Any const& any)
            -> decltype(numpy::proxy::conjugate{}(any))
            {
                return numpy::proxy::conjugate{}(any);
            }

        PROXY_IMPL(pythonic::__dispatch__, conjugate);

    }

}

#endif

