#ifndef PYTHONIC_NUMPY_UNWRAP_HPP
#define PYTHONIC_NUMPY_UNWRAP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/pi.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> unwrap(E const& expr, double discont = pi)
            {
                discont = nt2::max(discont, pi);
                types::ndarray<double, types::numpy_expr_to_ndarray<E>::N> out(expr.shape, __builtin__::None);
                auto arr = asarray(expr);
                auto iter = arr.fbegin();
                auto out_iter = out.fbegin();
                *out_iter++ = *iter++;
                for(auto end = arr.fend() ; iter != end; ++iter, ++out_iter)
                {
                    auto val = *iter;
                    if(nt2::abs(*(out_iter - 1) - val) > discont)
                        *out_iter = val + 2*pi * int((*(out_iter - 1) - val) / (discont));
                    else
                        *out_iter = val;
                }
                return out;
            }

        PROXY(pythonic::numpy, unwrap)

    }

}

#endif

