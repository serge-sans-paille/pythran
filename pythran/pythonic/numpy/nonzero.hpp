#ifndef PYTHONIC_NUMPY_NONZERO_HPP
#define PYTHONIC_NUMPY_NONZERO_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto nonzero(E const& expr) -> types::array<types::ndarray<long,1>, types::numpy_expr_to_ndarray<E>::N>
            {
                constexpr long N = types::numpy_expr_to_ndarray<E>::N;
                typedef types::array<types::ndarray<long,1>, N> out_type;
                long sz = expr.size();
                auto eshape = expr.shape;
                long *buffer = new long[N * sz]; // too much memory used
                long *buffer_iter = buffer;
                long real_sz = 0;
                for(long i=0; i< sz; ++i) {
                    if(expr.at(i)) {
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
                out_type out;
                types::array<long, 1> shape{{real_sz}};
                for(long i=0; i<N; ++i)
                {
                    out[i] = types::ndarray<long, 1>(shape, __builtin__::None);
                    for(long j=0; j<real_sz; ++j)
                        out[i][j] = buffer[j * N + i];
                }
                return out;
            }

        PROXY(pythonic::numpy, nonzero)

    }

}

#endif

