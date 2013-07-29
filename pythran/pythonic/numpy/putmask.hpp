#ifndef PYTHONIC_NUMPY_PUTMASK_HPP
#define PYTHONIC_NUMPY_PUTMASK_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class E,class F>
            types::none_type putmask(types::ndarray<T,N> & expr, E const& mask, F const& values)
            {
                for(size_t i=0; i<expr.size(); ++i)
                    if(mask.at(i))
                        expr.at(i) = values.at(i%values.size());
                return __builtin__::None;
            }
        PROXY(pythonic::numpy, putmask);

    }

}

#endif

