#ifndef PYTHONIC_NUMPY_ANY_HPP
#define PYTHONIC_NUMPY_ANY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/add.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            bool _any(E begin, E end, utils::int_<1>)
            {
                return std::any_of(begin, end, [](typename std::iterator_traits<E>::value_type e) -> bool { return e; });
            }
        template<class E, size_t N>
            bool _any(E begin, E end, utils::int_<N>)
            {
                for(; begin != end; ++begin) {
                    if(_any((*begin).begin(), (*begin).end(), utils::int_<N - 1>()))
                        return true;
                }
                return false;
            }

        template<class E>
            bool
            any(E const& expr, types::none_type _ = types::none_type()) {
                return _any(expr.begin(), expr.end(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
            }

        template<class E>
            auto any(E const& array, long axis)
            -> typename std::enable_if<E::value == 1, decltype(any(array))>::type
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return any(array);
            }

        template<class E>
            typename std::enable_if<E::value != 1, types::ndarray<typename E::dtype, E::value - 1>>::type
            any(E const& array, long axis)
            {
                constexpr long N = E::value;
                typedef typename E::dtype T;
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape();
                if(axis==0)
                {
                    types::array<long, N> shp;
                    shp[0] = 1;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin() + 1);
                    types::ndarray<bool,N> out(shp, false);
                    return std::accumulate(array.begin(), array.end(), *out.begin(), numpy::proxy::add());
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<bool,N-1> anyy(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), anyy.begin(), [=](types::ndarray<T,N-1> const& other) {return any(other, axis-1);});
                    return anyy;
                }
            }


        PROXY(pythonic::numpy, any);

    }

}

#endif

