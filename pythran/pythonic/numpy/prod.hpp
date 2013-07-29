#ifndef PYTHONIC_NUMPY_PROD_HPP
#define PYTHONIC_NUMPY_PROD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

#include <algorithm>

namespace pythonic {

    namespace numpy {
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type::dtype
            prod(E const& expr, types::none_type axis=__builtin__::None) {
                auto p = typename types::numpy_expr_to_ndarray<E>::type::dtype(1);
                for(long i=0, n = expr.size() ; i<n; ++i)
                    p *= expr.at(i);
                return p;
            }

        template<class T>
            T prod( types::ndarray<T,1> const& array, long axis)
            {
                if(axis!=0)
                    throw types::ValueError("axis out of bounds");
                return prod(array);
            }

        template<class T, size_t N>
            typename types::ndarray<T,N>::value_type prod( types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    return std::accumulate(array.begin() + 1, array.end(), *array.begin(), std::multiplies<typename types::ndarray<T,N>::value_type>());
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<T,N-1> prody(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), prody.begin(), [=](types::ndarray<T,N-1> const& other) {return prod(other, axis-1);});
                    return prody;
                }
            }

        PROXY(pythonic::numpy, prod);

    }

}

#endif

