#ifndef PYTHONIC_OPERATOR_IADD__HPP
#define PYTHONIC_OPERATOR_IADD__HPP

#include "pythran/pythonic/include/operator_/__iadd__.hpp"

#include "pythonic/operator_/iadd.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __iadd__, iadd);

    }

}

#endif

