#ifndef PYTHONIC_NUMPY_TRANSPOSE_HPP
#define PYTHONIC_NUMPY_TRANSPOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {

        template<class T>
            types::numpy_texpr<types::ndarray<T, 2>>
            transpose(types::ndarray<T, 2> const& arr) {
                return types::numpy_texpr<types::ndarray<T, 2>>(arr);
            }

        template<class T, unsigned long N, class... C>
            types::ndarray<T,N> _transpose(types::ndarray<T,N> const & a, long const l[N])
            {
                auto shape = a.shape();
                types::array<long, N> shp;
                for(unsigned long i=0; i<N; ++i)
                    shp[i] = shape[l[i]];

                types::ndarray<T,N> new_array(shp, __builtin__::None);

                types::array<long, N> new_strides;
                new_strides[N-1] = 1;
                std::transform(new_strides.rbegin(), new_strides.rend() -1, shp.rbegin(), new_strides.rbegin() + 1, std::multiplies<long>());

                types::array<long, N> old_strides;
                old_strides[N-1] = 1;
                std::transform(old_strides.rbegin(), old_strides.rend() -1, shape.rbegin(), old_strides.rbegin() + 1, std::multiplies<long>());

                auto iter = a.buffer,
                     iter_end = a.buffer + a.flat_size();
                for(long i=0; iter!=iter_end; ++iter, ++i) {
                    long offset = 0;
                    for(unsigned long s=0; s<N; s++)
                        offset += ((i/old_strides[l[s]]) % shape[l[s]])*new_strides[s];
                    new_array.buffer[offset] = *iter;
                }

                return new_array;
            }

        template<class T, size_t N>
            types::ndarray<T,N> transpose(types::ndarray<T,N> const & a)
            {
                long t[N];
                for(unsigned long i = 0; i<N; ++i)
                    t[N-1-i] = i;
                return _transpose(a, t);
            }
        template<class T, size_t N, size_t M>
            types::ndarray<T,N> transpose(types::ndarray<T,N> const & a, types::array<long, M> const& t)
            {
                static_assert(N==M, "axes don't match array");

                long val = t[M-1];
                if(val>=long(N))
                    throw types::ValueError("invalid axis for this array");
                return _transpose(a, &t[0]);
            }

        NUMPY_EXPR_TO_NDARRAY0(transpose);
        PROXY(pythonic::numpy, transpose);

    }

}

#endif

