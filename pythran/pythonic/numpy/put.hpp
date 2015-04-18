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
                for(size_t i=0; i<ind.flat_size(); ++i)
                {
                    auto val = *(vind.fbegin() + i);
                    if(static_cast<size_t>(val) >= expr.flat_size() || val <0)
                        throw types::ValueError("indice out of bound");
                    *(expr.fbegin() + val) = *(vv.fbegin() + i%vv.flat_size());
                }
                return __builtin__::None;
            }

        template<class T, size_t N>
            types::none_type put(types::ndarray<T,N> & expr, long ind, T const& v)
            {
                if(static_cast<size_t>(ind) >= expr.flat_size() || ind <0)
                    throw types::ValueError("indice out of bound");
                *(expr.fbegin() + ind) = v;
                return __builtin__::None;
            }

        template<class E, class M, class V>
          types::none_type put(E&, M const&, V const&) {
            throw std::runtime_error("put only partially implemented");
          }
        PROXY(pythonic::numpy, put);

    }

}

#endif

