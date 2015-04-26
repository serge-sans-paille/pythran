#ifndef PYTHONIC_OPERATOR_TRUEDIV__HPP
#define PYTHONIC_OPERATOR_TRUEDIV__HPP

#include "pythran/pythonic/include/operator_/__truediv__.hpp"

#include "pythonic/operator_/truediv.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __truediv__, truediv);

    }

}

#endif

