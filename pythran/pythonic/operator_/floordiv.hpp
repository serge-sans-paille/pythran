#ifndef PYTHONIC_OPERATOR_FLOORDIV_HPP
#define PYTHONIC_OPERATOR_FLOORDIV_HPP

#include "pythonic/utils/proxy.hpp"
#include <nt2/include/functions/divfloor.hpp>

namespace pythonic {

    namespace operator_ {
        long floordiv(long a, long b) {
            return std::floor(static_cast<double>(a)/b);
        }
        long floordiv(double a, long b) {
            return std::floor(a/b);
        }

        long floordiv(long a, double b) {
            return std::floor(a/b);
        }

        long floordiv(double a, double b) {
            return std::floor(a/b);
        }
        PROXY(pythonic::operator_, floordiv);

    }

}

#endif

