#ifndef PYTHONIC_OPERATOR_MUL__HPP
#define PYTHONIC_OPERATOR_MUL__HPP

#include "pythran/pythonic/include/operator_/__mul__.hpp"

#include "pythonic/operator_/mul.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __mul__, mul);

    }

}

#endif

