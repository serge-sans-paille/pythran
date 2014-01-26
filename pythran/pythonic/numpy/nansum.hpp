#ifndef PYTHONIC_NUMPY_NANSUM_HPP
#define PYTHONIC_NUMPY_NANSUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_type.hpp"

#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            typename types::numpy_expr_to_ndarray<E>::type::dtype
            nansum(E const& expr) {
                typename types::numpy_expr_to_ndarray<E>::type::dtype s=0;
                long n = expr.size();
                for(long i=0;i<n;++i) {
                    auto e_i = expr.at(i);
                    if(not nt2::is_nan(e_i))
                        s += e_i ;
                }
                return s;
            }

        PROXY(pythonic::numpy, nansum);

    }

}

#endif

