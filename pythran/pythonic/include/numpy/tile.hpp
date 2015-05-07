#ifndef PYTHONIC_INCLUDE_NUMPY_TILE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TILE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O>
            void _tile(I begin, I end, O& out, utils::int_<1>);

        template<class I, class O, size_t N>
            void _tile(I begin, I end, O& out, utils::int_<N>);

        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type tile(E const& expr, int reps);

        template<class E, size_t N>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, N> tile(E const& expr, types::array<long, N> const& reps);

        PROXY_DECL(pythonic::numpy, tile);

    }

}

#endif
