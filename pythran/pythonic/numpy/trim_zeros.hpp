#ifndef PYTHONIC_NUMPY_TRIMZEROS_HPP
#define PYTHONIC_NUMPY_TRIMZEROS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T>
            types::ndarray<T,1> trim_zeros(types::ndarray<T,1> const& expr, types::str const& trim = "fb")
            {
                int begin = 0;
                int end = expr.size();
                if(trim.find("f") != std::string::npos)
                    begin = std::find_if(expr.fbegin(), expr.fend(), [](T i){return i!=0;}) - expr.fbegin();
                if(trim.find("b") != std::string::npos)
                    while(*(expr.fbegin() + --end) != 0);
                types::ndarray<T,1> out(types::array<long,1>{{end - begin}}, __builtin__::None);
                std::copy(expr.fbegin() + begin, expr.fbegin() + end, out.fbegin());
                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(trim_zeros)
            PROXY(pythonic::numpy, trim_zeros)

    }

}

#endif

