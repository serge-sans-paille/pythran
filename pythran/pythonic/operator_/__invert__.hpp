#ifndef PYTHONIC_OPERATOR_INVERT__HPP
#define PYTHONIC_OPERATOR_INVERT__HPP

#include "pythran/pythonic/include/operator_/__invert__.hpp"

#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __invert__, invert);

    }

}

#endif

