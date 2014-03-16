#ifndef PYTHONIC_NUMPY_ALL_HPP
#define PYTHONIC_NUMPY_ALL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/multiply.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            bool _all(E begin, E end, utils::int_<1>)
            {
                return std::all_of(begin, end, [](typename std::iterator_traits<E>::value_type e) -> bool { return e; });
            }
        template<class E, size_t N>
            bool _all(E begin, E end, utils::int_<N>)
            {
                for( ;begin != end; ++begin) {
                    if(not _all((*begin).begin(), (*begin).end(), utils::int_<N - 1>()))
                        return false;
                }
                return true;
            }
            
        template<class E>
            bool
            all(E const& expr, types::none_type _ = types::none_type()) {
                return _all(expr.begin(), expr.end(), utils::int_<types::numpy_expr_to_ndarray<E>::N>());
            }

        template<class T>
            bool all(types::ndarray<T,1> const& array, long axis)
            {
                if(axis != 0)
                    throw types::ValueError("axis out of bounds");
                return all(array);
            }

        template<class T, size_t N>
            types::ndarray<bool,N - 1>
            all(types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    types::array<long, N> shp;
                    shp[0] = 1;
                    std::copy(shape.begin() + 1, shape.end(), shp.begin() + 1);
                    types::ndarray<bool,N> out(shp, true);
                    return std::accumulate(array.begin(), array.end(), *out.begin(), numpy::proxy::multiply());
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<bool ,N-1> ally(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), ally.begin(), [=](types::ndarray<T,N-1> const& other) {return all(other, axis-1);});
                    return ally;
                }
            }

        PROXY(pythonic::numpy, all);

    }

}

#endif

