#ifndef PYTHONIC_NUMPY_PUT_HPP
#define PYTHONIC_NUMPY_PUT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic {

    namespace numpy {
        template<class F, class T, size_t N, class E>
            typename std::enable_if<types::is_numexpr_arg<F>::value, types::none_type>::type
            put(types::ndarray<T,N> & expr, F const& ind, E const& v)
            {
                auto vind = asarray(ind);
                auto vv = asarray(v);
                for(size_t i=0; i<ind.size(); ++i)
                {
                    auto val = *(vind.fbegin() + i);
                    if(val>=expr.size() || val <0)
                        throw types::ValueError("indice out of bound");
                    *(expr.fbegin() + val) = *(vv.fbegin() + i%vv.size());
                }
                return __builtin__::None;
            }

        template<class T, size_t N>
            types::none_type put(types::ndarray<T,N> & expr, int ind, T const& v)
            {
                if(ind>=expr.size() || ind <0)
                    throw types::ValueError("indice out of bound");
                *(expr.fbegin() + ind) = v;
                return __builtin__::None;
            }

        NUMPY_EXPR_TO_NDARRAY0(put);
        PROXY(pythonic::numpy, put);

    }

}

#endif

