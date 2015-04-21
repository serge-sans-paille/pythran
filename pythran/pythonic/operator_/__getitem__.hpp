#ifndef PYTHONIC_OPERATOR_GETITEM__HPP
#define PYTHONIC_OPERATOR_GETITEM__HPP

#include "pythran/pythonic/include/operator_/__getitem__.hpp"

#include "pythonic/operator_/getitem.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __getitem__, getitem);

    }

}

#endif

