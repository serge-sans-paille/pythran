#ifndef PYTHONIC_NUMPY_NANARGMAX_HPP
#define PYTHONIC_NUMPY_NANARGMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            long nanargmax(E&& expr) {
                long sz = expr.size();
                if(not sz) 
                    throw types::ValueError("empty sequence");
                long i = 0;
                auto e_i = expr.at(i);
                while(i< sz and nt2::is_nan(e_i)) {
                    e_i = expr.at(++i);
                }
                if( i < sz) {
                    auto res = e_i;
                    auto index = i;
                    for(; i< sz ; ++i) {
                        auto e_i = expr.at(i);
                        if(e_i > res and not nt2::is_nan(e_i)) {
                            res = e_i;
                            index = i;
                        }
                    }
                    return index;
                }
                else
                    throw types::ValueError("empty sequence");
            }
        PROXY(pythonic::numpy, nanargmax);

    }

}

#endif

