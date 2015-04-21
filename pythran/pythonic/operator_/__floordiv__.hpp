#ifndef PYTHONIC_OPERATOR_FLOORDIV__HPP
#define PYTHONIC_OPERATOR_FLOORDIV__HPP

#include "pythran/pythonic/include/operator_/__floordiv__.hpp"

#include "pythonic/operator_/floordiv.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, __floordiv__, floordiv);

    }

}

#endif

