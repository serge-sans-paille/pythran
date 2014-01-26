#ifndef PYTHONIC_NUMPY_DIFF_HPP
#define PYTHONIC_NUMPY_DIFF_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type
            diff(E const& expr, long n=1) {
                decltype(expr.shape) shape(expr.shape);
                --shape[types::numpy_expr_to_ndarray<E>::N-1];

                typename types::numpy_expr_to_ndarray<E>::type out(shape, __builtin__::None);
                auto slice = expr.shape[types::numpy_expr_to_ndarray<E>::N-1];
                long j = 0;
                for(long i = 0, n = expr.size(); i< n ; i+=slice) {
                    auto prev = expr.at(i);
                    for(long k = 1; k< slice ; ++k) {
                        auto nprev = expr.at(i+k);
                        out.at(j++) = nprev - prev;
                        prev = nprev;
                    }
                }
                if(n==1) return out;
                else return diff(out, n-1); // TODO: inplace modification to avoid n-1 allocations
            }

        PROXY(pythonic::numpy, diff);

    }

}

#endif

