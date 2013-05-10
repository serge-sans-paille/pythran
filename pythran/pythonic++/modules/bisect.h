#ifndef PYTHONIC_MODULE_BISECT_H
#define PYTHONIC_MODULE_BISECT_H
#include <algorithm>
namespace pythonic {
    namespace bisect {
        template <class X, class A>
            size_t bisect_left(X const& x, A const& a, long lo=0, long hi=-1) {
                if(hi<0) hi = x.end() - x.begin();
                return std::lower_bound(x.begin()+lo, x.begin()+hi, a) - x.begin();
            }

        PROXY(pythonic::bisect, bisect_left);

        template <class X, class A>
            size_t bisect(X const& x, A const& a, long lo=0, long hi=-1) {
                if(hi<0) hi = x.end() - x.begin();
                return std::upper_bound(x.begin()+lo, x.begin()+hi, a) - x.begin();
            }

        PROXY(pythonic::bisect, bisect);

        template<class X, class A>
            size_t bisect_right(X const& x, A const& a, long lo=0, long hi=-1)
            {
                return bisect(x, a, lo, hi);
            }
        PROXY(pythonic::bisect, bisect_right);

    }
}
#endif
