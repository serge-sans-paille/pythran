#ifndef PYTHONIC_NUMPY_FLATNONZERO_HPP
#define PYTHONIC_NUMPY_FLATNONZERO_HPP

#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O>
            void _flatnonzero(I begin, I end, O& out, long& i, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++i)
                    if(*begin) {
                        *out++ = i;
                    }
            }
        template<class I, class O, size_t N>
            void _flatnonzero(I begin, I end, O& out, long& i, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _flatnonzero((*begin).begin(), (*begin).end(), out, i, utils::int_<N - 1>());
            }

        template<class E>
            types::ndarray<long, 1> flatnonzero(E const& expr) {
                long n = expr.flat_size();
                long *buffer = (long*)malloc(sizeof(long) * n);
                long *iter = buffer;
                long i = 0;
                _flatnonzero(expr.begin(), expr.end(), iter, i, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                long shape[1] = { iter - buffer };
                return types::ndarray<long, 1>(buffer, shape);
            }

        PROXY(pythonic::numpy, flatnonzero);

    }

}

#endif

