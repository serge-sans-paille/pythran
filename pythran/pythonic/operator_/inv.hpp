#ifndef PYTHONIC_OPERATOR_INV_HPP
#define PYTHONIC_OPERATOR_INV_HPP

#include "pythran/pythonic/include/operator_/inv.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythran/pythonic/include/operator_/inv.hpp"

#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY_IMPL(pythonic::operator_, inv, invert);
    }

}

#endif

