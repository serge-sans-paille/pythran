#ifndef PYTHONIC_NUMPY_TRIMZEROS_HPP
#define PYTHONIC_NUMPY_TRIMZEROS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_gexpr.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            types::numpy_gexpr<T, types::contiguous_slice> trim_zeros(T const& expr, types::str const& trim = "fb")
            {
                static_assert(types::numpy_expr_to_ndarray<T>::N == 1,
                              "Not implemented : trim_zeroes only works for 1D array");

                int begin = 0;
                int end = expr.size();
                if(trim.find("f") != std::string::npos)
                    begin = std::find_if(expr.begin(), expr.end(),
                                         [](typename types::numpy_expr_to_ndarray<T>::T i){return i!=0;}) - expr.begin();
                if(trim.find("b") != std::string::npos)
                    while(*(expr.begin() + --end) != 0);
                return types::numpy_gexpr<T, types::contiguous_slice>(expr, types::contiguous_slice(begin, end));
            }

            PROXY(pythonic::numpy, trim_zeros)

    }

}

#endif

