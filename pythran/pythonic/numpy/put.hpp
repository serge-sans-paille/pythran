#ifndef PYTHONIC_NUMPY_PUT_HPP
#define PYTHONIC_NUMPY_PUT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_conversion.hpp"

namespace pythonic {

    namespace numpy {
        template<class F, class T, size_t N, class E>
            typename std::enable_if<types::is_array_like<F>::value, types::none_type>::type put(types::ndarray<T,N> & expr, F const& ind, E const& v)
            {
                for(size_t i=0; i<ind.size(); ++i)
                {
                    auto val = ind.at(i);
                    if(val>=expr.size() || val <0)
                        throw types::ValueError("indice out of bound");
                    expr.at(val) = v.at(i%v.size());
                }
                return __builtin__::None;
            }

        template<class T, size_t N>
            types::none_type put(types::ndarray<T,N> & expr, int ind, T const& v)
            {
                if(ind>=expr.size() || ind <0)
                    throw types::ValueError("indice out of bound");
                expr.at(ind) = v;
                return __builtin__::None;
            }

        NUMPY_EXPR_TO_NDARRAY0(put);
        PROXY(pythonic::numpy, put);

    }

}

#endif

