#ifndef PYTHONIC_NUMPY_INDICES_HPP
#define PYTHONIC_NUMPY_INDICES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<size_t N, class dtype=long>
            types::ndarray<dtype, N+1> indices(types::array<long, N> const& shape, dtype d = dtype()) {
                types::array<long, N+1> oshape;
                oshape[0] = N ;
                std::copy(shape.begin(), shape.end(), oshape.begin() + 1);
                types::ndarray<dtype, N+1> out(oshape, __builtin__::None);
                dtype* iters[N];
                for(size_t n=0; n<N; ++n) 
                    iters[n]=out[n].buffer;
                size_t lens[N];
                lens[0] = out.size() / shape[0];
                for(size_t n=1; n<N; ++n) 
                    lens[n] = lens[n-1] / shape[n];
                for(long i=0, n=out.size()/N; i<n;++i) {
                    long mult = 1;
                    for(long n=N-1; n>0; n--) {
                        *(iters[n]++) = (i/mult)%shape[n];
                        mult *= shape[n];
                    }
                    *(iters[0]++) = i/mult;
                }
                return out;
            }

        PROXY(pythonic::numpy, indices);

    }

}

#endif

