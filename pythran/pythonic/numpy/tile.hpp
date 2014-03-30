#ifndef PYTHONIC_NUMPY_TILE_HPP
#define PYTHONIC_NUMPY_TILE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O>
            void _tile(I begin, I end, O& out, utils::int_<1>)
            {
                out = std::copy(begin, end, out);
            }
        template<class I, class O, size_t N>
            void _tile(I begin, I end, O& out, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _tile((*begin).begin(), (*begin).end(), out, utils::int_<N - 1>());
            }

        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type tile(E const& expr, int reps)
            {
                size_t n = expr.size();
                typename types::numpy_expr_to_ndarray<E>::type out(types::array<long, 1>{{long(n * reps)}}, __builtin__::None);
                auto out_iter = out.fbegin();
                _tile(expr.begin(), expr.end(), out_iter, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                for(int i = 1; i< reps; ++i)
                    out_iter = std::copy(out.fbegin(), out.fbegin() + n, out_iter);
                return out;
            }

        template<class E, size_t N>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, N> tile(E const& expr, types::array<long, N> const& reps)
            {
                size_t n = expr.size();
                types::array<long, N> shape;
                for(size_t i=0; i<N; ++i)
                    shape[N - i - 1] = reps[N - i - 1] * ((E::value > i)?expr.shape[i]:1);
                types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, N> out(shape, __builtin__::None);
                auto out_iter = out.fbegin();
                _tile(expr.begin(), expr.end(), out_iter, utils::int_<types::numpy_expr_to_ndarray<E>::N>());

                size_t nreps = out.size() / n;
                for(size_t i = 1; i< nreps; ++i)
                    out_iter = std::copy(out.fbegin(), out.fbegin() + n, out_iter);
                return out;
            }

        PROXY(pythonic::numpy, tile);

    }

}

#endif

