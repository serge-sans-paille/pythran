#ifndef PYTHONIC_NUMPY_REPEAT_HPP
#define PYTHONIC_NUMPY_REPEAT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,1> repeat(types::ndarray<T,N> const& expr, int repeats)
            {
                types::ndarray<T,1> out(types::array<long, N>{{expr.size() * repeats}}, __builtin__::None);
                for(int i=0; i<out.size(); ++i)
                    out.at(i) = expr.at(i / expr.size());
                return out;
            }

        NUMPY_EXPR_TO_NDARRAY0(repeat);
        PROXY(pythonic::numpy, repeat);

    }

}

#endif

