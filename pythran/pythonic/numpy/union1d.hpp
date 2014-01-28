#ifndef PYTHONIC_NUMPY_UNION1D_HPP
#define PYTHONIC_NUMPY_UNION1D_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            types::ndarray<decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::T>() + std::declval<typename types::numpy_expr_to_ndarray<F>::T>()), 1> union1d(E const& e, F const& f)
            {
                std::set<decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::T>() + std::declval<typename types::numpy_expr_to_ndarray<F>::T>())> res;
                for(size_t i=0; i<e.size(); ++i)
                    res.insert(e.at(i));
                for(size_t i=0; i<f.size(); ++i)
                    res.insert(f.at(i));
                return types::ndarray<decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::T>() + std::declval<typename types::numpy_expr_to_ndarray<F>::T>()), 1>(res);
            }

        PROXY(pythonic::numpy, union1d)

    }

}

#endif

