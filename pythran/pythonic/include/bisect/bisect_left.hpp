#ifndef PYTHONIC_INCLUDE_BISECT_BISECTLEFT_HPP
#define PYTHONIC_INCLUDE_BISECT_BISECTLEFT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace bisect {
        template <class X, class A>
            size_t bisect_left(X const& x, A const& a, long lo=0, long hi=-1);

        PROXY_DECL(pythonic::bisect, bisect_left);

    }

}

#endif
