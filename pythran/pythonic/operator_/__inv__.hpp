#ifndef PYTHONIC_OPERATOR_INV__HPP
#define PYTHONIC_OPERATOR_INV__HPP

#include "pythran/pythonic/include/operator_/__inv__.hpp"

#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __inv__, invert);

    }

}

#endif

