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
                bool any_true = false;
                while(not any_true and begin != end) {
                    any_true = _any((*begin).begin(), (*begin).end(), utils::int_<N - 1>());
                    ++begin;
                }
                return any_true;
            }
            
        template<class E>
            bool
            any(E const& expr, types::none_type _ = types::none_type()) {
                return _any(expr.begin(), expr.end(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
            }

        template<class T>
            bool any(types::ndarray<T,1> const& array, long axis)
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return any(array);
            }

        template<class T, size_t N>
            typename types::ndarray<bool,N>::value_type
            any(types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    return std::accumulate(array.begin() + 1, array.end(), *array.begin(), numpy::proxy::add());
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

