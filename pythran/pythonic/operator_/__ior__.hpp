#ifndef PYTHONIC_OPERATOR_IOR__HPP
#define PYTHONIC_OPERATOR_IOR__HPP

#include "pythran/pythonic/include/operator_/__ior__.hpp"

#include "pythonic/operator_/ior.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __ior__, ior);

    }

}

#endif

