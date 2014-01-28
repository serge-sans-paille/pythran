#ifndef PYTHONIC_NUMPY_TILE_HPP
#define PYTHONIC_NUMPY_TILE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type tile(E const& expr, int reps)
            {
                typename types::numpy_expr_to_ndarray<E>::type out(types::array<long, 1>{{expr.size() * reps}}, __builtin__::None);
                for(size_t i=0; i<expr.size(); ++i)
                    out.buffer[i] = expr.at(i);
                for(size_t i=expr.size(); i<expr.size() * reps; ++i)
                    out.buffer[i] = out.buffer[i%expr.size()];
                return out;
            }

        template<class E, size_t N>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, N> tile(E const& expr, types::array<long, N> const& reps)
            {
                types::array<long, N> shape;
                for(size_t i=0; i<N; ++i)
                    shape[N - i - 1] = reps[N - i - 1] * ((E::value > i)?expr.shape[i]:1);
                types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, N> out(shape, __builtin__::None);
                for(size_t i=0; i<expr.size(); ++i)
                    out.buffer[i] = expr.at(i);
                for(size_t i=expr.size(); i<out.size(); ++i)
                    out.buffer[i] = out.buffer[i%expr.size()];
                return out;
            }

        PROXY(pythonic::numpy, tile);

    }

}

#endif

