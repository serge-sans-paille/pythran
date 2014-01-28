#ifndef PYTHONIC_NUMPY_EDIFF1D_HPP
#define PYTHONIC_NUMPY_EDIFF1D_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::type::dtype, 1>
            ediff1d(E const& expr)
            {
                long n = expr.size() -1 ;
                types::ndarray<typename types::numpy_expr_to_ndarray<E>::type::dtype, 1> out(types::make_tuple(n), __builtin__::None);
                auto prev = expr.at(0);
                for(long i=0; i< n ; ++i) {
                    auto next = expr.at(i+1);
                    out.at(i) = next - prev;
                    prev = next;
                }
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

