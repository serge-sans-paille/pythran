#ifndef PYTHONIC_NUMPY_EDIFF1D_HPP
#define PYTHONIC_NUMPY_EDIFF1D_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>
            ediff1d(E const& expr)
            {
                auto arr = asarray(expr);
                long n = arr.size() -1 ;
                types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1> out(types::make_tuple(n), __builtin__::None);
                // Compute adjacent difference except for the first element
                std::adjacent_difference (arr.fbegin() + 1, arr.fend(), out.fbegin());
                // First element can be done now
                (*out.fbegin()) = *(arr.fbegin()+1) - *(arr.fbegin());
                return out;
            }

        template<class E>
            auto ediff1d(types::list<E> const & expr) -> decltype(ediff1d(asarray(expr))) {
                return ediff1d(asarray(expr));
            }

        PROXY(pythonic::numpy, ediff1d);

    }

}

#endif

