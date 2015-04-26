#ifndef PYTHONIC_OPERATOR_IDIV__HPP
#define PYTHONIC_OPERATOR_IDIV__HPP

#include "pythran/pythonic/include/operator_/__idiv__.hpp"

#include "pythonic/operator_/idiv.hpp"

namespace pythonic {

    namespace operator_ {

        FPROXY_IMPL(pythonic::operator_, __idiv__, idiv);
    }

}

#endif

