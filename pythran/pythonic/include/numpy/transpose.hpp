#ifndef PYTHONIC_INCLUDE_NUMPY_TRANSPOSE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRANSPOSE_HPP

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
            transpose(types::ndarray<T, 2> const& arr);

        template<class T, unsigned long N, class... C>
            types::ndarray<T,N> _transpose(types::ndarray<T,N> const & a, long const l[N]);

        template<class T, size_t N>
            types::ndarray<T,N> transpose(types::ndarray<T,N> const & a);

        template<class T, size_t N, size_t M>
            types::ndarray<T,N> transpose(types::ndarray<T,N> const & a, types::array<long, M> const& t);

        NUMPY_EXPR_TO_NDARRAY0_DECL(transpose);
        PROXY_DECL(pythonic::numpy, transpose);

    }

}

#endif
