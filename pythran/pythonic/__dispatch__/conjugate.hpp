#ifndef PYTHONIC_DISPATCH_CONJUGATE_HPP
#define PYTHONIC_DISPATCH_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/conjugate.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto conjugate(Any const& any) -> decltype(numpy::proxy::conjugate{}(any)) {return numpy::proxy::conjugate{}(any);}

        PROXY(pythonic::__dispatch__, conjugate);

    }

}

#endif

