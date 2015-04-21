#ifndef PYTHONIC_OPERATOR_RSHIFT__HPP
#define PYTHONIC_OPERATOR_RSHIFT__HPP

#include "pythran/pythonic/include/operator_/__rshift__.hpp"

#include "pythonic/operator_/rshift.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __rshift__, rshift);

    }

}

#endif

