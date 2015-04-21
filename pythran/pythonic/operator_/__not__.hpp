#ifndef PYTHONIC_OPERATOR_NOT__HPP
#define PYTHONIC_OPERATOR_NOT__HPP

#include "pythran/pythonic/include/operator_/__not__.hpp"

#include "pythonic/operator_/not_.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __not__, not_);

    }

}

#endif

