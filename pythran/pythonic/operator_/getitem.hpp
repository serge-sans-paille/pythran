#ifndef PYTHONIC_OPERATOR_GETITEM_HPP
#define PYTHONIC_OPERATOR_GETITEM_HPP

#include "pythran/pythonic/include/operator_/getitem.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto getitem(A const& a, B const& b) -> decltype(a[b])
            {
                return a[b];
            }

        PROXY_IMPL(pythonic::operator_, getitem);

    }

}

#endif
