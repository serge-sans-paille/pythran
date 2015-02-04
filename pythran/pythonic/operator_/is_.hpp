#ifndef PYTHONIC_OPERATOR_IS_HPP
#define PYTHONIC_OPERATOR_IS_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto is_(A const& a, B const& b) -> decltype(a==b){
                return a==b;
            }
        PROXY(pythonic::operator_, is_);
    }

}

#endif

