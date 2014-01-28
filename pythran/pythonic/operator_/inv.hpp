#ifndef PYTHONIC_OPERATOR_INV_HPP
#define PYTHONIC_OPERATOR_INV_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace operator_ {
        FPROXY(pythonic::operator_, inv, invert);
    }

}

#endif

