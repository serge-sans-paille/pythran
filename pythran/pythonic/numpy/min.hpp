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
                    min = std::min(min, *begin);
            }
        template<class E, class F, size_t N>
            void _min(E begin, E end, F& min, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _min((*begin).begin(), (*begin).end(), min, utils::int_<N - 1>());
            }
            
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::T
            min(E const& expr, types::none_type _ = types::none_type()) {
                typename types::numpy_expr_to_ndarray<E>::T p = std::numeric_limits<typename types::numpy_expr_to_ndarray<E>::T>::max();
                _min(expr.begin(), expr.end(), p, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return p;
            }

        template<class T>
            T min(types::ndarray<T,1> const& array, long axis)
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return min(array);
            }

        template<class T, size_t N>
            typename types::ndarray<T,N>::value_type
            min(types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    return std::accumulate(array.begin() + 1, array.end(), *array.begin(), numpy::proxy::minimum());
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<T,N-1> miny(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), miny.begin(), [=](types::ndarray<T,N-1> const& other) {return min(other, axis-1);});
                    return miny;
                }
            }

        PROXY(pythonic::numpy, min);

    }

}

#endif

