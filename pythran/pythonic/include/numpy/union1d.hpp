#ifndef PYTHONIC_INCLUDE_NUMPY_UNION1D_HPP
#define PYTHONIC_INCLUDE_NUMPY_UNION1D_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O>
            void _union1d(I begin, I end, O& out, utils::int_<1>);

        template<class I, class O, size_t N>
            void _union1d(I begin, I end, O& out, utils::int_<N>);

        template<class E, class F>
            types::ndarray<decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::T>() + std::declval<typename types::numpy_expr_to_ndarray<F>::T>()), 1>
            union1d(E const& e, F const& f);

        PROXY_DECL(pythonic::numpy, union1d)

    }

}

#endif
