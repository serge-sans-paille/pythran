#ifndef PYTHONIC_OPERATOR_IPOW__HPP
#define PYTHONIC_OPERATOR_IPOW__HPP

#include "pythran/pythonic/include/operator_/__ipow__.hpp"

#include "pythonic/operator_/ipow.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __ipow__, ipow);

    }

}

#endif

