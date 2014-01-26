#ifndef PYTHONIC_NUMPY_CLIP_HPP
#define PYTHONIC_NUMPY_CLIP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class Mi, class Ma>
            typename types::numpy_expr_to_ndarray<E>::type clip(E const& e, Mi a_min, Ma a_max) {
                typename types::numpy_expr_to_ndarray<E>::type out(e.shape, __builtin__::None);
                auto out_iter = out.buffer;
                for(long i=0, n=e.size(); i<n; ++i) {
                    auto v = e.at(i);
                    if(v<a_min) v=a_min;
                    else if(v>a_max) v = a_max;
                    *out_iter++ = v;
                }
                return out;
            }

        PROXY(pythonic::numpy, clip);

    }

}

#endif

