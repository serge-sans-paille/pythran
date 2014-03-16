#ifndef PYTHONIC_NUMPY_PTP_HPP
#define PYTHONIC_NUMPY_PTP_HPP

#include "pythonic/numpy/min.hpp"
#include "pythonic/numpy/max.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto ptp(E const& expr, long axis) -> decltype(max(expr, axis) - min(expr, axis))
            {
                auto min_ =  min(expr, axis);
                auto max_ = max(expr, axis);
                return max_ - min_;
            }

        template<class E>
            auto ptp(E const& expr) -> decltype(max(expr) - min(expr))
            {
                return max(expr) - min(expr);
            }

        PROXY(pythonic::numpy, ptp);

    }

}

#endif

