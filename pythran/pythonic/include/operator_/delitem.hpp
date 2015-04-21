#ifndef PYTHONIC_INCLUDE_OPERATOR_DELITEM_HPP
#define PYTHONIC_INCLUDE_OPERATOR_DELITEM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/None.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            types::none_type delitem(A&& a, B const& b);

        PROXY_DECL(pythonic::operator_, delitem);

    }

}

#endif
