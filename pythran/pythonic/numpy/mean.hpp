#ifndef PYTHONIC_NUMPY_MEAN_HPP
#define PYTHONIC_NUMPY_MEAN_HPP

#include "pythonic/numpy/sum.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class dtype=double>
            auto
            mean(E const& expr, types::none_type axis=__builtin__::None, dtype d=dtype())
            -> decltype(sum(expr)/typename types::numpy_type<dtype>::type(expr.size()))
            {
                return sum(expr)/typename types::numpy_type<dtype>::type(expr.size());
            }

        PROXY(pythonic::numpy, mean);

    }

}

#endif

