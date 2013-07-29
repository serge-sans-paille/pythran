#ifndef PYTHONIC_NUMPY_CUMSUM_HPP
#define PYTHONIC_NUMPY_CUMSUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class dtype=T>
            types::ndarray<typename types::numpy_type<dtype>::type,1> cumsum(types::ndarray<T,N> const& expr, dtype d = dtype()) {
                long count = expr.size();
                types::ndarray<typename types::numpy_type<dtype>::type,1> cumsumy(types::make_tuple(count), __builtin__::None);
                std::partial_sum(expr.buffer, expr.buffer + count, cumsumy.buffer);
                return cumsumy;
            }

        template<class T, class dtype=T>
            types::ndarray<typename types::numpy_type<dtype>::type,1> cumsum(types::ndarray<T,1> const& expr, long axis, dtype d = dtype()) {
                if(axis !=0)
                    throw types::ValueError("axis out of bounds");
                return cumsum(expr);
            }

        template<class T, size_t N, class dtype=T>
            types::ndarray<typename types::numpy_type<dtype>::type,N> cumsum(types::ndarray<T,N> const& expr, long axis, dtype d = dtype()) {
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

