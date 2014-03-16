#ifndef PYTHONIC_NUMPY_TRIU_HPP
#define PYTHONIC_NUMPY_TRIU_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            types::ndarray<T,2> triu(types::ndarray<T,2> const& expr, int k = 0)
            {
                types::ndarray<T,2> out(expr.shape, __builtin__::None);
                for(int i=0; i<expr.shape[0]; ++i)
                    for(long j=0 ; j<expr.shape[1]; ++j)
                        if( j - i >= k)
                            out[i][j] = expr[i][j];
                        else
                            out[i][j] = 0;
                return out;

            }
        NUMPY_EXPR_TO_NDARRAY0(triu)
            PROXY(pythonic::numpy, triu)

    }

}

#endif

