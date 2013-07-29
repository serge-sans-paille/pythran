#ifndef PYTHONIC_NUMPY_DIGITIZE_HPP
#define PYTHONIC_NUMPY_DIGITIZE_HPP

#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class F>
            types::ndarray< long, 1 >
            digitize(E const& expr, F const& b) {
                auto bins = asarray(b);
                bool is_increasing = bins.size() > 1 and bins.at(0) < bins.at(1);
                types::ndarray<long, 1> out(types::make_tuple(long(expr.size())), __builtin__::None);
                if(is_increasing) {
                    for(long i = 0, n = expr.size(); i< n; ++i)
                        out.at(i) = std::lower_bound(bins.begin(), bins.end(), expr.at(i)) - bins.begin();
                }
                else {
                    for(long i = 0, n = expr.size(); i< n; ++i)
                        out.at(i) = std::lower_bound(bins.begin(), bins.end(), expr.at(i), operator_::proxy::gt()) - bins.begin();
                }
                return out;
            }

        PROXY(pythonic::numpy, digitize);

    }

}

#endif

