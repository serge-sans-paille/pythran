#ifndef PYTHONIC_NUMPY_CUMPROD_HPP
#define PYTHONIC_NUMPY_CUMPROD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class dtype=T>
            types::ndarray<typename types::numpy_type<dtype>::type,1> cumprod(types::ndarray<T,N> const& expr, dtype d = dtype()) {
                long count = expr.size();
                types::ndarray<typename types::numpy_type<dtype>::type,1> cumprody(types::make_tuple(count), __builtin__::None);
                std::partial_sum(expr.buffer, expr.buffer + count, cumprody.buffer, std::multiplies<T>());
                return cumprody;
            }

        template<class T, class dtype=T>
            types::ndarray<typename types::numpy_type<dtype>::type,1> cumprod(types::ndarray<T,1> const& expr, long axis, dtype d = dtype()) {
                if(axis !=0)
                    throw types::ValueError("axis out of bounds");
                return cumprod(expr);
            }

        template<class T, size_t N, class dtype=T>
            types::ndarray<typename types::numpy_type<dtype>::type,N> cumprod(types::ndarray<T,N> const& expr, long axis, dtype d = dtype()) {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");

                auto shape = expr.shape;
                types::ndarray<typename types::numpy_type<dtype>::type,N> cumprody(shape, __builtin__::None);
                if(axis==0) {
                    std::copy(expr.buffer, expr.buffer + shape[N-1], cumprody.buffer);
                    std::transform(cumprody.begin(), cumprody.end()-1, expr.begin() + 1, cumprody.begin() + 1, std::multiplies<types::ndarray<T,N-1>>());
                }
                else {
                    std::transform(expr.begin(), expr.end(), cumprody.begin(), [=](types::ndarray<T,N-1> const& e) { return cumprod(e, axis-1, d); });
                }
                return cumprody;
            }

        PROXY(pythonic::numpy, cumprod);

    }

}

#endif

