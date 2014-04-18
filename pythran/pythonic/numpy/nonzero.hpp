#ifndef PYTHONIC_NUMPY_NONZERO_HPP
#define PYTHONIC_NUMPY_NONZERO_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O, size_t M>
            void _nonzero(I begin, I end, O& out, types::array<long, M>& curr, utils::int_<1>)
            {
                I start = begin;
                for(; begin != end; ++begin) {
                    curr[M - 1] = begin - start;
                    if(*begin) {
                        for(size_t i = 0; i < M; ++i) {
                            *(out[i]) = curr[i];
                            ++out[i];
                        }
                    }
                }
            }
        template<class I, class O, size_t M, size_t N>
            void _nonzero(I begin, I end, O& out, types::array<long, M>& curr, utils::int_<N>)
            {
                I start = begin;
                for(; begin != end; ++begin) {
                    curr[M - N] = begin - start;
                    _nonzero((*begin).begin(), (*begin).end(), out, curr, utils::int_<N - 1>());
                }
            }

        template<class E>
            auto nonzero(E const& expr) -> types::array<types::ndarray<long,1>, types::numpy_expr_to_ndarray<E>::N>
            {
                constexpr long N = types::numpy_expr_to_ndarray<E>::N;
                typedef types::array<types::ndarray<long,1>, N> out_type;
                long sz = expr.size();

                types::array<long *, N> out_buffers;
                types::array<long *, N> out_iters;
                for(size_t i = 0; i < N ; ++i)
                    out_iters[i] = out_buffers[i] = (long*)malloc(sz * sizeof(long)); // too much memory used

                types::array<long, N> indices;
                _nonzero(expr.begin(), expr.end(), out_iters, indices, utils::int_<N>());

                long shape[] = { out_iters[0] - out_buffers[0] };

                out_type out;
                for(size_t i = 0; i < N ; ++i)
                    out[i] = types::ndarray<long, 1>(out_buffers[i], shape);

                return out;
            }

        PROXY(pythonic::numpy, nonzero)

    }

}

#endif

