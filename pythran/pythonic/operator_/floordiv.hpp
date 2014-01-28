#ifndef PYTHONIC_OPERATOR_FLOORDIV_HPP
#define PYTHONIC_OPERATOR_FLOORDIV_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/exceptions.hpp"
#include <nt2/include/functions/divfloor.hpp>

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto floordiv(A const& a, B const& b) -> decltype(nt2::divfloor(a,b)){
                return nt2::divfloor(a,b);
            }
        PROXY(pythonic::operator_, floordiv);

    }

}

#endif

