#ifndef PYTHONIC_BISECT_BISECTLEFT_HPP
#define PYTHONIC_BISECT_BISECTLEFT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/bisect/bisect_left.hpp"

#include <algorithm>

namespace pythonic {

    namespace bisect {
        template <class X, class A>
            size_t bisect_left(X const& x, A const& a, long lo, long hi) {
                if(hi<0) hi = x.end() - x.begin();
                return std::lower_bound(x.begin()+lo, x.begin()+hi, a) - x.begin();
            }

        PROXY_IMPL(pythonic::bisect, bisect_left);

    }

}

#endif
