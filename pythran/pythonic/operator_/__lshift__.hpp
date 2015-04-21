#ifndef PYTHONIC_OPERATOR_LSHIFT__HPP
#define PYTHONIC_OPERATOR_LSHIFT__HPP

#include "pythran/pythonic/include/operator_/__lshift__.hpp"

#include "pythonic/operator_/lshift.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __lshift__, lshift);

    }

}

#endif

