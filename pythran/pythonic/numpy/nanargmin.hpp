#ifndef PYTHONIC_NUMPY_NANARGMIN_HPP
#define PYTHONIC_NUMPY_NANARGMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            long nanargmin(E&& expr) {
                long sz = expr.size();
                if(not sz) 
                    throw types::ValueError("empty sequence");
                long i = 0;
                auto e_i = expr.at(i);
                for(; i< sz and nt2::is_nan(e_i) ; ++i) {
                    e_i = expr.at(i);
                }
                if( i < sz) {
                    auto res = e_i;
                    auto index = i;
                    for(; i< sz ; ++i) {
                        auto e_i = expr.at(i);
                        if(e_i< res and not nt2::is_nan(e_i)) {
                            res = e_i;
                            index = i;
                        }
                    }
                    return index;
                }
                else
                    throw types::ValueError("empty sequence");
            }
        PROXY(pythonic::numpy, nanargmin);

    }

}

#endif

