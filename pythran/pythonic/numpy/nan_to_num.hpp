#ifndef PYTHONIC_NUMPY_NANTONUM_HPP
#define PYTHONIC_NUMPY_NANTONUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <limits>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_positive.hpp>
#include <nt2/include/functions/is_negative.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type
            nan_to_num(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::type out(expr.shape, __builtin__::None);
                for(long i=0, n=expr.size(); i<n; ++i) {
                    auto v = expr.at(i);
                    if(nt2::is_inf(v) and nt2::is_positive(v))
                        out.at(i) = std::numeric_limits<typename types::numpy_expr_to_ndarray<E>::type::dtype>::max();
                    else if(nt2::is_inf(v) and nt2::is_negative(v))
                        out.at(i) = -std::numeric_limits<typename types::numpy_expr_to_ndarray<E>::type::dtype>::max();
                    else if(nt2::is_nan(v))
                        out.at(i) = 0;
                    else out.at(i) = v;
                }
                return out;
            }

        PROXY(pythonic::numpy, nan_to_num);

    }

}

#endif

