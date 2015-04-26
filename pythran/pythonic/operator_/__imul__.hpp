#ifndef PYTHONIC_OPERATOR_IMUL__HPP
#define PYTHONIC_OPERATOR_IMUL__HPP

#include "pythran/pythonic/include/operator_/__imul__.hpp"

#include "pythonic/operator_/imul.hpp"

namespace pythonic {

    namespace operator_ {

        FPROXY_IMPL(pythonic::operator_, __imul__, imul);
    }

}

#endif

