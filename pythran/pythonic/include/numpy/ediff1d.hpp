#ifndef PYTHONIC_INCLUDE_NUMPY_EDIFF1D_HPP
#define PYTHONIC_INCLUDE_NUMPY_EDIFF1D_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>
            ediff1d(E const& expr);

        template<class E>
            auto ediff1d(types::list<E> const & expr)
            -> decltype(ediff1d(asarray(expr)));

        PROXY_DECL(pythonic::numpy, ediff1d);

    }

}

#endif
