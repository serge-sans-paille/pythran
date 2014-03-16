#ifndef PYTHONIC_NUMPY_UNION1D_HPP
#define PYTHONIC_NUMPY_UNION1D_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O>
            void _union1d(I begin, I end, O& out, utils::int_<1>)
            {
                for(; begin != end; ++begin)
                    out.insert(*begin);
            }
        template<class I, class O, size_t N>
            void _union1d(I begin, I end, O& out, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _union1d((*begin).begin(), (*begin).end(), out, utils::int_<N - 1>());
            }
        template<class E, class F>
            types::ndarray<decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::T>() + std::declval<typename types::numpy_expr_to_ndarray<F>::T>()), 1>
            union1d(E const& e, F const& f)
            {
                std::set<decltype(std::declval<typename types::numpy_expr_to_ndarray<E>::T>() + std::declval<typename types::numpy_expr_to_ndarray<F>::T>())> res;
                _union1d(e.begin(), e.end(), res, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                _union1d(f.begin(), f.end(), res, utils::int_<types::numpy_expr_to_ndarray<F>::N>());
                return res;
            }

        PROXY(pythonic::numpy, union1d)

    }

}

#endif

