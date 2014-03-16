#ifndef PYTHONIC_NUMPY_PLACE_HPP
#define PYTHONIC_NUMPY_PLACE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class Tp, size_t Np, class F>
            types::none_type place(types::ndarray<T,N> & expr, types::ndarray<Tp,Np> const& mask, F const& values)
            {
                auto first = expr.fend();
                auto viter = values.begin(), vend = values.end();
                auto miter = mask.fbegin();
                for(auto iter = expr.fbegin(), end = expr.fend(); iter != end; ++iter, ++miter)
                {
                    if(*miter)
                    {
                        if(first == expr.fend())
                            first = iter;
                        if(viter != vend) {
                            *iter = *viter;
                            ++viter;
                        }
                        else
                        {
                            *iter = *first;
                        }
                    }
                }
                return __builtin__::None;
            }
        template<class T, size_t N, class M, class F>
            types::none_type place(types::ndarray<T,N> & expr, M const& mask, F const& values)
            {
                return place(expr, asarray(mask), values);
            }
        PROXY(pythonic::numpy, place);

    }

}

#endif

