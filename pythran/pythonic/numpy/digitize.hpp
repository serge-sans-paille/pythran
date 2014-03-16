#ifndef PYTHONIC_NUMPY_DIGITIZE_HPP
#define PYTHONIC_NUMPY_DIGITIZE_HPP

#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/operator_/gt.hpp"
#include "pythonic/operator_/lt.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O, class B, class Op>
            void _digitize(I begin, I end, O& out, B& bins, Op const& op, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++out)
                    *out = std::lower_bound(bins.begin(), bins.end(), *begin, op) - bins.begin();
            }
        template<class I, class O, class B, class Op, size_t N>
            void _digitize(I begin, I end, O& out, B& bins, Op const& op, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _digitize((*begin).begin(), (*begin).end(), out, bins, op, utils::int_<N - 1>());
            }

        template<class E, class F>
            types::ndarray< long, 1 >
            digitize(E const& expr, F const& b) {
                auto bins = asarray(b);
                bool is_increasing = bins.size() > 1 and *bins.fbegin() < *(bins.fbegin() +1);
                types::ndarray<long, 1> out(types::make_tuple(long(expr.size())), __builtin__::None);
                auto out_iter = out.fbegin();
                if(is_increasing) {
                    _digitize(expr.begin(), expr.end(), out_iter, bins, operator_::proxy::lt(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                }
                else {
                    _digitize(expr.begin(), expr.end(), out_iter, bins, operator_::proxy::gt(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                }
                return out;
            }

        PROXY(pythonic::numpy, digitize);

    }

}

#endif

