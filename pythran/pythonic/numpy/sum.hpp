#ifndef PYTHONIC_NUMPY_SUM_HPP
#define PYTHONIC_NUMPY_SUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/add.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _sum(E begin, E end, F& sum, utils::int_<1>)
            {
                sum = std::accumulate(begin, end, sum, std::plus<F>());
            }
        template<class E, class F, size_t N>
            void _sum(E begin, E end, F& sum, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _sum((*begin).begin(), (*begin).end(), sum, utils::int_<N - 1>());
            }

        template<class E>
            typename
            std::conditional<std::is_same<typename E::dtype, bool>::value,
                             long,
                             typename E::dtype
                            >::type
            sum(E const& expr, types::none_type _ = types::none_type()) {
                typename std::conditional<std::is_same<typename E::dtype, bool>::value,
                                          long,
                                          typename E::dtype
                                         >::type p = 0;
                _sum(expr.begin(), expr.end(), p, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return p;
            }

        template<class E>
            auto sum(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(sum(array))>::type
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return sum(array);
            }

        template<class E>
            typename std::enable_if<E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
            sum(E const& array, long axis)
            {
                if(axis<0 || axis >= E::value)
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    types::array<long, E::value - 1> shp;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin());
                    types::ndarray<typename E::dtype, E::value - 1> out(shp, 0);
                    return std::accumulate(array.begin(), array.end(), out, proxy::add());
                }
                else
                {
                    types::array<long, E::value-1> shp;
                    auto next = std::copy(shape.begin(), shape.begin() + axis, shp.begin());
                    std::copy(shape.begin() + axis + 1, shape.end(), next);
                    types::ndarray<typename E::dtype, E::value-1> sumy(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), sumy.begin(), [axis](decltype((*array.begin())) other) { return sum(other, axis - 1); });
                    return sumy;
                }
            }

        PROXY(pythonic::numpy, sum);

    }

}

#endif

