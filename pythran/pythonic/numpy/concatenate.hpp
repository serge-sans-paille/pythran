#ifndef PYTHONIC_NUMPY_CONCATENATE_HPP
#define PYTHONIC_NUMPY_CONCATENATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, size_t M>
            types::ndarray<T,N> concatenate(types::array<types::ndarray<T,N>, M> const & ai) {
                long n = 1;
                long shape[N];
                shape[0] = 0L;
                for(auto const& a : ai) {
                    shape[0] += a.shape[0];
                    n *= a.size();
                }
                std::copy(ai[0].shape.begin() +1 , ai[0].shape.end(), &shape[1]);

                T* buffer = new T[n];
                T* iter = buffer;
                for(auto const& a : ai) 
                    iter = std::copy(a.buffer, a.buffer + a.size(), iter);

                return types::ndarray<T,N>(buffer, shape);
            }
        PROXY(pythonic::numpy, concatenate);

    }

}

#endif

