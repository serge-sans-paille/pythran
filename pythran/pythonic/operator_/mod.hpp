#ifndef PYTHONIC_OPERATOR_MOD_HPP
#define PYTHONIC_OPERATOR_MOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto mod(A const& a, B const& b)
            -> typename std::enable_if<std::is_fundamental<A>::value and std::is_fundamental<B>::value,
                                       decltype(a % b)>::type
            {
                auto t = a % b;
                return t < 0 ? (t + b) : t;
            }
        inline double mod(double a, long b) {
            auto t = std::fmod(a, double(b));
            return t < 0 ? (t + b) : t;
        }
        inline double mod(double a, double b) {
            auto t = std::fmod(a, b);
            return t < 0 ? (t + b) : t;
        }
        template<class A, class B>
            auto mod(A const& a, B const& b) // for ndarrays
            -> typename std::enable_if<not std::is_fundamental<A>::value or not std::is_fundamental<B>::value,
                                       decltype(a%b)>::type
            {
                return a % b;
            }
        PROXY(pythonic::operator_, mod);
    }

}

#endif

