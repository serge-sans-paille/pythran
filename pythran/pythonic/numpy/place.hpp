#ifndef PYTHONIC_NUMPY_PLACE_HPP
#define PYTHONIC_NUMPY_PLACE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N, class E,class F>
            types::none_type place(types::ndarray<T,N> & expr, E const& mask, F const& values)
            {
                int j=0;
                int first = -1;
                for(size_t i=0; i<expr.size(); ++i)
                {
                    if(mask.at(i))
                    {
                        if(first==-1)
                            first = i;
                        if(j<values.size())
                            expr.at(i) = values.at(j++);
                        else
                        {
                            expr.at(i) = expr.at(first);
                        }
                    }
                }
                return __builtin__::None;
            }
        PROXY(pythonic::numpy, place);

    }

}

#endif

