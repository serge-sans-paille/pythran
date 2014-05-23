#ifndef PYTHONIC_NUMPY_DIAG_HPP
#define PYTHONIC_NUMPY_DIAG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            types::ndarray<T,1> diag(types::ndarray<T,2> const &a, long k=0) {
                T* buffer = (T*)malloc(std::max(a.shape[0], a.shape[1]) * sizeof(T));
                long shape[1] = {0};
                auto iter = buffer;
                if(k>=0)
                    for(int i=0, j = k; i< a.shape[0] and j < a.shape[1]; ++i, ++j, ++shape[0])
                        *iter++ = a[i][j];
                else {
                    for(int i=-k, j = 0; i< a.shape[0] and j < a.shape[1]; ++i, ++j, ++shape[0])
                        *iter++ = a[i][j];
                }
                return types::ndarray<T,1>(buffer, shape);
            }

        template<class T>
            types::ndarray<T,2> diag(types::ndarray<T,1> const &a, long k=0) {
                long n = a.size() + std::abs(k);
                types::ndarray<T,2> out(types::make_tuple(n,n), 0);
                if(k>=0)
                    for(long i=0,j =k ; i< n and j<n ;++i,++j)
                        out[i][j] = a[i];
                else
                    for(long i=-k,j =0 ; i< n and j<n ;++i,++j)
                        out[i][j] = a[j];
                return out;
            }
        template<class T>
            auto diag(types::list<T> const &a, long k=0) 
            -> decltype(diag(asarray(a), k))
            {
                return diag(asarray(a), k);
            }

        NUMPY_EXPR_TO_NDARRAY0(diag);
        PROXY(pythonic::numpy, diag);

    }

}

#endif

