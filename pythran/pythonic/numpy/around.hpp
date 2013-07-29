#ifndef PYTHONIC_NUMPY_AROUND_HPP
#define PYTHONIC_NUMPY_AROUND_HPP

#include "pythonic/numpy/rint.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto around(E const& a, long decimals=0) -> decltype(rint(a * std::pow(typename types::numpy_expr_to_ndarray<E>::type::dtype(10),decimals)) / std::pow(typename types::numpy_expr_to_ndarray<E>::type::dtype(10), decimals)) {
                return rint(a * std::pow(typename types::numpy_expr_to_ndarray<E>::type::dtype(10),decimals)) / std::pow(typename types::numpy_expr_to_ndarray<E>::type::dtype(10), decimals);
            }
        template<class T>
            typename types::numpy_expr_to_ndarray<types::list<T>>::type around(types::list<T> const& l, long decimals=0) {
                return around(typename types::numpy_expr_to_ndarray<types::list<T>>::type(l), decimals);
            }

        PROXY(pythonic::numpy, around);

    }

}

#endif

