#ifndef PYTHONIC_INCLUDE_OPERATOR_IAND_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IAND_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            A iand(A  a, B const& b);

        PROXY_DECL(pythonic::operator_, iand);

    }

}

#endif
