#ifndef PYTHONIC_DISPATCH_COPY_HPP
#define PYTHONIC_DISPATCH_COPY_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __dispatch__ {
        template<class Any>
            auto copy(Any const& any) -> decltype(any.copy()) {return any.copy();}

        PROXY(pythonic::__dispatch__, copy);

    }

}

#endif

