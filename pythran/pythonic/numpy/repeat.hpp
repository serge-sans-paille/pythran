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
                types::ndarray<T,1> out(types::array<long, 1>{{expr.size() * repeats}}, __builtin__::None);
                auto out_iter = out.fbegin();
                for(auto iter = expr.fbegin(), end = expr.fend(); iter != end; ++iter)
                    for(int i = 0; i< repeats; ++i)
                        *out_iter++ = *iter;
                return out;
            }

        NUMPY_EXPR_TO_NDARRAY0(repeat);
        PROXY(pythonic::numpy, repeat);

    }

}

#endif

