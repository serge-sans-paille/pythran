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

        template<class T>
            auto sum(types::ndarray<T,1> const& array, long axis)
            -> decltype(sum(array))
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return sum(array);
            }

        template<class T, size_t N>
            types::ndarray<T,N-1>
            sum(types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    types::array<long, N> shp;
                    shp[0] = 1;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin() + 1);
                    types::ndarray<T,N> out(shp, 0);
                    return std::accumulate(array.begin(), array.end(), *out.begin(), proxy::add());
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<T,N-1> sumy(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), sumy.begin(), [=](types::ndarray<T,N-1> const& other) {return sum(other, axis-1);});
                    return sumy;
                }
            }

        template<class E>
            auto sum(E const& expr, long axis)
            -> decltype(sum(typename types::numpy_expr_to_ndarray<E>::type(expr), axis))
            {
                return sum(typename types::numpy_expr_to_ndarray<E>::type(expr), axis);
            }

        PROXY(pythonic::numpy, sum);

    }

}

#endif

