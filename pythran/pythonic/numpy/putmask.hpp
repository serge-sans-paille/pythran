#ifndef PYTHONIC_NUMPY_PUTMASK_HPP
#define PYTHONIC_NUMPY_PUTMASK_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class E,class F>
            types::none_type putmask(types::ndarray<T,N> & expr, E const& mask, F const& values)
            {
                auto amask = asarray(mask);
                auto avalues = asarray(values);
                auto iexpr = expr.fbegin();
                auto n = avalues.size();
                for(size_t i=0; i<expr.size(); ++i)
                    if(*(amask.fbegin() +i))
                        *(iexpr + i) = *(avalues.fbegin() + i % n);
                return __builtin__::None;
            }
        PROXY(pythonic::numpy, putmask);

    }

}

#endif

