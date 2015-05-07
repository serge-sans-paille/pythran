#ifndef PYTHONIC_NUMPY_MEAN_HPP
#define PYTHONIC_NUMPY_MEAN_HPP

#include "pythonic/include/numpy/mean.hpp"

#include "pythonic/numpy/sum.hpp"
#include "pythonic/types/numpy_type.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace numpy {
        template<class E, class dtype>
            auto mean(E const& expr, types::none_type axis, dtype d)
            -> decltype(sum(expr)/typename types::numpy_type<dtype>::type(expr.flat_size()))
            {
                return sum(expr) / typename types::numpy_type<dtype>::type(expr.flat_size());
            }

        template<class E, class dtype>
            auto mean(E const& expr, long axis, dtype d)
            -> decltype(sum(expr, axis))
            {
                return sum(expr, axis) /= typename types::numpy_type<dtype>::type(expr.shape()[axis]);
            }

        PROXY_IMPL(pythonic::numpy, mean);

    }

}

#endif
