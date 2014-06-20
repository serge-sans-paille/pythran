#ifndef PYTHONIC_NUMPY_MAX_HPP
#define PYTHONIC_NUMPY_MAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/maximum.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _max(E begin, E end, F& max, utils::int_<1>)
            {
                for(; begin != end; ++begin)
                    max = nt2::max(max, *begin);
            }
        template<class E, class F, size_t N>
            void _max(E begin, E end, F& max, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _max((*begin).begin(), (*begin).end(), max, utils::int_<N - 1>());
            }

        template<class E>
            typename E::dtype
            max(E const& expr, types::none_type _ = types::none_type()) {
                typename E::dtype p = std::numeric_limits<typename E::dtype>::lowest();
                _max(expr.begin(), expr.end(), p, utils::int_<E::value>());
                return p;
            }

        template<class E>
            auto max(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(max(array))>::type
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return max(array);
            }

        template<class E>
            typename std::enable_if<E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
            max(E const& array, long axis)
            {
                if(axis<0 || axis >= E::value)
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    types::array<long, E::value - 1> shp;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin());
                    types::ndarray<typename E::dtype, E::value - 1> out(shp, std::numeric_limits<typename E::dtype>::lowest());
                    return std::accumulate(array.begin(), array.end(), out, proxy::maximum());
                }
                else
                {
                    types::array<long, E::value-1> shp;
                    auto next = std::copy(shape.begin(), shape.begin() + axis, shp.begin());
                    std::copy(shape.begin() + axis + 1, shape.end(), next);
                    types::ndarray<typename E::dtype,E::value-1> maxy(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), maxy.begin(), [axis](decltype((*array.begin())) other) {return max(other, axis-1);});
                    return maxy;
                }
            }

        PROXY(pythonic::numpy, max);

    }

}

#endif

