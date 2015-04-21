#ifndef PYTHONIC_NUMPY_ARGWHERE_HPP
#define PYTHONIC_NUMPY_ARGWHERE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            typename types::ndarray<long, 2>
            argwhere(E const& expr) {
                typedef typename types::ndarray<long, 2> out_type;
                constexpr long N = types::numpy_expr_to_ndarray<E>::N;
                auto arr = asarray(expr);
                long sz = arr.flat_size();
                auto eshape = arr.shape();

                long *buffer = (long*)malloc(sz * N * sizeof(long)); // too much memory used
                long *buffer_iter = buffer;

                long real_sz = 0;
                auto iter = arr.fbegin();
                for(long i=0; i< sz; ++i, ++iter) {
                    if(*iter) {
                        ++real_sz;
                        long mult = 1;
                        for(long j=N-1; j>0; j--) {
                            buffer_iter[j] = (i/mult)%eshape[j];
                            mult*=eshape[j];
                        }
                        buffer_iter[0] = i/mult;
                        buffer_iter+=N;
                    }
                }
                long shape[2] = { real_sz, N };
                return out_type(buffer, shape);
            }

        PROXY(pythonic::numpy, argwhere);

    }

}

#endif

