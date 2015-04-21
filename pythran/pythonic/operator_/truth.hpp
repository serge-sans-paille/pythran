#ifndef PYTHONIC_OPERATOR_TRUTH_HPP
#define PYTHONIC_OPERATOR_TRUTH_HPP

#include "pythran/pythonic/include/operator_/truth.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        bool truth(bool const& a)
        {
            return a;
        }

        PROXY_IMPL(pythonic::operator_, truth);
    }

}

#endif
