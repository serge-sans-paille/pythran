#ifndef PYTHONIC_OPERATOR_SUB__HPP
#define PYTHONIC_OPERATOR_SUB__HPP

#include "pythran/pythonic/include/operator_/__sub__.hpp"

#include "pythonic/operator_/sub.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __sub__, sub);

    }

}

#endif

