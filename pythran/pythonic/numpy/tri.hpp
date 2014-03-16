#ifndef PYTHONIC_NUMPY_TRI_HPP
#define PYTHONIC_NUMPY_TRI_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class dtype = double>
            types::ndarray<typename types::numpy_type<dtype>::type, 2> tri(int N, int M=-1, int k=0, dtype d=dtype())
            {
                if(M==-1)
                    M = N;
                types::ndarray<typename types::numpy_type<dtype>::type, 2> out(types::array<long,2>{{N, M}}, 0); 
                for(int i=0; i<N; ++i)
                    for(long j=0 ; j<M; ++j)
                        if( j - i <= k)
                            out[i][j] = 1;
                return out;
            }

        PROXY(pythonic::numpy, tri)

    }

}

#endif

