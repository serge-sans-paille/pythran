#ifndef PYTHONIC_NUMPY_ROLL_HPP
#define PYTHONIC_NUMPY_ROLL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> roll(types::ndarray<T,N> const& expr, int shift)
            {
                while(shift<0) shift+=expr.size();
                shift %=expr.size();;
                types::ndarray<T,N> out(expr.shape, __builtin__::None);
                std::copy(expr.fbegin(), expr.fend() - shift, std::copy(expr.fend() - shift, expr.fend(), out.fbegin()));
                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(roll)
            PROXY(pythonic::numpy, roll);

    }

}

#endif

