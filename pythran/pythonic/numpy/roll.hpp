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
                for(int i=shift; i<expr.size(); ++i)
                    out.at(i) = expr.at(i - shift);
                for(int i=0; i<shift; ++i)
                    out.at(i) = expr.at(i + expr.size() - shift);

                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(roll)
            PROXY(pythonic::numpy, roll);

    }

}

#endif

