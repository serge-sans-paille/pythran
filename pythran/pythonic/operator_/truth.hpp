#ifndef PYTHONIC_OPERATOR_TRUTH;_HPP
#define PYTHONIC_OPERATOR_TRUTH;_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        bool truth(bool const& a) {
            return a;
        }

        PROXY(pythonic::operator_, truth);
    }

}

#endif

