#ifndef PYTHONIC_NUMPY_UNWRAP_HPP
#define PYTHONIC_NUMPY_UNWRAP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/pi.hpp"

#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> unwrap(E const& expr, double discont = pi)
            {
                discont = nt2::max(discont, pi);
                types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> out(expr.shape, __builtin__::None);
                out.buffer[0] = expr.at(0);
                for(size_t i=1; i<out.size(); ++i)
                {
                    auto val = expr.at(i);
                    if(nt2::abs(out.buffer[i-1] - val) > discont)
                        out.buffer[i] = val + 2*pi * int((out.buffer[i-1] - val) / (discont));
                    else
                        out.buffer[i] = val;
                }
                return out;
            }

        PROXY(pythonic::numpy, unwrap)

    }

}

#endif

