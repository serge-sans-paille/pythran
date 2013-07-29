#ifndef PYTHONIC_NUMPY_ALLCLOSE_HPP
#define PYTHONIC_NUMPY_ALLCLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class U, class V>
            bool allclose(U&& u, V&& v, double rtol=1e-5, double atol=1e-8) {
                long u_s = u.size(),
                     v_s = v.size();
                if( u_s == v_s ) {
                    for(long i=0;i < u_s; ++i) {
                        auto v_i = v.at(i);
                        auto u_i = u.at(i);
                        if( nt2::is_nan(v_i) ||
                                nt2::is_nan(u_i) ||
                                std::abs(u.at(i)-v_i) > (atol + rtol * std::abs(v_i)))
                            return false;
                    }
                    return true;
                }
                return false;
            }

        PROXY(pythonic::numpy, allclose);

    }

}

#endif

