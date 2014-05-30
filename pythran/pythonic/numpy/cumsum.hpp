#ifndef PYTHONIC_NUMPY_CUMSUM_HPP
#define PYTHONIC_NUMPY_CUMSUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class O, class F>
            F _partial_sum(E begin, E end, O& out, F psum, utils::int_<1>)
            {
                for(; begin != end ; ++begin, ++out)
                    *out = psum += *begin;
                return psum;
            }
        template<class E, class O, class F, size_t N>
            F _partial_sum(E begin, E end, O& out, F psum, utils::int_<N>)
            {
                for(; begin != end ; ++begin)
                    psum = _partial_sum((*begin).begin(), (*begin).end(), out, psum, utils::int_<N - 1>());
                return psum;
            }
        template<class E, class dtype=typename E::dtype>
            types::ndarray<typename types::numpy_type<dtype>::type,1> cumsum(E const& expr, dtype d = dtype()) {
                long count = expr.size();
                types::ndarray<typename types::numpy_type<dtype>::type,1> cumsumy(types::make_tuple(count), __builtin__::None);
                auto oiter = cumsumy.fbegin();
                _partial_sum(expr.begin(), expr.end(), oiter, typename types::numpy_type<dtype>::type(0), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return cumsumy;
            }

        template<class E, class dtype=typename E::dtype>
            auto cumsum(E const& expr, long axis, dtype d = dtype())
            -> typename std::enable_if<E::value == 1, decltype(cumsum(expr))>::type
            {
                if(axis !=0)
                    throw types::ValueError("axis out of bounds");
                return cumsum(expr);
            }

        template<class T, size_t N, class dtype=T>
            auto cumsum(types::ndarray<T,N> const& expr, long axis, dtype d = dtype())
            -> typename std::enable_if<N != 1,  types::ndarray<typename types::numpy_type<dtype>::type,N>>::type
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");

                auto shape = expr.shape;
                types::ndarray<typename types::numpy_type<dtype>::type,N> cumsumy(shape, __builtin__::None);
                if(axis==0) {
                    std::copy(expr.buffer, expr.buffer + shape[N-1], cumsumy.buffer);
                    std::transform(cumsumy.begin(), cumsumy.end()-1, expr.begin() + 1, cumsumy.begin() + 1, std::plus<types::ndarray<T,N-1>>());
                }
                else {
                    std::transform(expr.begin(), expr.end(), cumsumy.begin(), [=](types::ndarray<T,N-1> const& e) { return cumsum(e, axis-1, d); });
                }
                return cumsumy;
            }

        PROXY(pythonic::numpy, cumsum);

    }

}

#endif

