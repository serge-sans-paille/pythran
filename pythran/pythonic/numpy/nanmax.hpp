#ifndef PYTHONIC_NUMPY_NANMAX_HPP
#define PYTHONIC_NUMPY_NANMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        template<class E>
            auto nanmax(E&& expr) -> typename std::remove_reference<decltype(expr.at(0))>::type {
                long n = expr.size();
                if(not n) 
                    throw types::ValueError("empty sequence");
                long i = 0;
                auto e_i = expr.at(i);
                while( nt2::is_nan(e_i) and i < n )
                    e_i = expr.at(++i);
                if(i == n) {
                    throw types::ValueError("nan sequence");
                }
                else {
                    auto res = e_i;
                    for(; i< n ; ++i) {
                        auto e_i = expr.at(i);
                        if(e_i > res and not nt2::is_nan(e_i))
                            res = e_i;
                    }
                    return res;
                }
            }

        PROXY(pythonic::numpy, nanmax);

    }

}

#endif

