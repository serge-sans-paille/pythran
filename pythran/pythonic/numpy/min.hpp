#ifndef PYTHONIC_NUMPY_MIN_HPP
#define PYTHONIC_NUMPY_MIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/minimum.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            void _min(E begin, E end, F& min, utils::int_<1>)
            {
                for(; begin != end; ++begin)
                    min = nt2::min(min, *begin);
            }
        template<class E, class F, size_t N>
            void _min(E begin, E end, F& min, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _min((*begin).begin(), (*begin).end(), min, utils::int_<N - 1>());
            }

        template<class E>
            typename E::dtype
            min(E const& expr, types::none_type _ = types::none_type()) {
                typename E::dtype p = std::numeric_limits<typename E::dtype>::max();
                _min(expr.begin(), expr.end(), p, utils::int_<E::value>());
                return p;
            }

        template<class E>
            auto min(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(min(array))>::type
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return min(array);
            }

        template<class E>
            typename std::enable_if<E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
            min(E const& array, long axis)
            {
                if(axis<0 || axis >= E::value)
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    types::array<long, E::value - 1> shp;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin());
                    types::ndarray<typename E::dtype, E::value - 1> out(shp, std::numeric_limits<typename E::dtype>::max());
                    return std::accumulate(array.begin(), array.end(), out, proxy::minimum());
                }
                else
                {
                    types::array<long, E::value-1> shp;
                    auto next = std::copy(shape.begin(), shape.begin() + axis, shp.begin());
                    std::copy(shape.begin() + axis + 1, shape.end(), next);
                    types::ndarray<typename E::dtype,E::value-1> miny(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), miny.begin(), [axis](decltype((*array.begin())) other) {return min(other, axis-1);});
                    return miny;
                }
            }

        PROXY(pythonic::numpy, min);

    }

}

#endif

