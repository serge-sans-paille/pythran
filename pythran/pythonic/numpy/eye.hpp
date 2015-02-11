#ifndef PYTHONIC_NUMPY_EYE_HPP
#define PYTHONIC_NUMPY_EYE_HPP

#include "pythonic/numpy/zeros.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {

        template<class dtype = double>
            types::ndarray<typename types::numpy_type<dtype>::type, 2> eye(long N, long M, long k=0, dtype d=dtype())
            {
                types::ndarray<typename types::numpy_type<dtype>::type, 2> out = zeros(types::make_tuple(N, M), d);
                if(k>=0)
                    for(int i=0, j = k; i< N and j < M; ++i, ++j)
                        out[i][j] = typename types::numpy_type<dtype>::type(1);
                else
                    for(int i=-k, j = 0; i< N and j < M; ++i, ++j)
                        out[i][j] = typename types::numpy_type<dtype>::type(1);
                return out;
            }

        template<class dtype = double>
            types::ndarray<typename types::numpy_type<dtype>::type, 2> eye(long N, types::none_type M=__builtin__::None, long k=0, dtype d=dtype())
            {
                return eye(N, N, k, d);
            }

        PROXY(pythonic::numpy, eye);

    }

}

#endif

