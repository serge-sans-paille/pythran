#ifndef PYTHONIC_NUMPY_RESIZE_HPP
#define PYTHONIC_NUMPY_RESIZE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,1> resize(types::ndarray<T,N> const& expr, int new_shape)
            {
                types::ndarray<T,1> out(types::array<long, N>{{new_shape}}, __builtin__::None);
                for(int i=0; i<new_shape; ++i)
                    out.at(i) = expr.at(i % expr.size());
                return out;
            }

        template<class T, size_t N, size_t M>
            types::ndarray<T,M> resize(types::ndarray<T,N> const& expr, types::array<long, M> const& new_shape)
            {
                types::ndarray<T,M> out(new_shape, __builtin__::None);
                for(size_t i=0; i<out.size(); ++i)
                    out.at(i) = expr.at(i % expr.size());
                return out;
            }

        NUMPY_EXPR_TO_NDARRAY0(resize);
        PROXY(pythonic::numpy, resize);

    }

}

#endif

