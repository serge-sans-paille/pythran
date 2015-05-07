#ifndef PYTHONIC_INCLUDE_NUMPY_NONZERO_HPP
#define PYTHONIC_INCLUDE_NUMPY_NONZERO_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O, size_t M>
            void _nonzero(I begin, I end, O& out, types::array<long, M>& curr, utils::int_<1>);

        template<class I, class O, size_t M, size_t N>
            void _nonzero(I begin, I end, O& out, types::array<long, M>& curr, utils::int_<N>);

        template<class E>
            auto nonzero(E const& expr) -> types::array<types::ndarray<long,1>, types::numpy_expr_to_ndarray<E>::N>;

        PROXY_DECL(pythonic::numpy, nonzero)

    }

}

#endif
