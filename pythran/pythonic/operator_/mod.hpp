#ifndef PYTHONIC_OPERATOR_MOD_HPP
#define PYTHONIC_OPERATOR_MOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace operator_ {

        //SG: we have to deal with python modulo that always return a positive value
        //but without using conditional because this function is also used for expression
        //templates at the numpy level
        template <class A, class B>
            auto mod(A const& a, B const& b) -> decltype(((a % b) + b) % b) {
                return ((a % b) + b) % b;
            }
        inline double mod(double a, long b) {
            auto t = std::fmod(a, double(b));
            return t < 0 ? (t + b) : t;
        }
        inline double mod(double a, double b) {
            auto t = std::fmod(a, b);
            return t < 0 ? (t + b) : t;
        }
        template<class T>
        inline auto mod(types::str const& s, T const& b)
        -> decltype(s%b)
        {
            return s % b;
        }
        PROXY(pythonic::operator_, mod);
    }

}

#endif

