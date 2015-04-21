#ifndef PYTHONIC_OPERATOR_NEG__HPP
#define PYTHONIC_OPERATOR_NEG__HPP

#include "pythran/pythonic/include/operator_/__neg__.hpp"

#include "pythonic/operator_/neg.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __neg__, neg);

    }

}

#endif

