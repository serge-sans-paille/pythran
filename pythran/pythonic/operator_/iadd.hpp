#ifndef PYTHONIC_OPERATOR_IADD_HPP
#define PYTHONIC_OPERATOR_IADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/set.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            A iadd(A a, B const& b) {
                return a+=b;
            }

        template <class A>
            auto iadd(types::empty_list, types::list<A> const& b) -> decltype(b) {
                return b;
            }

        template <class K, class V>
            auto iadd(types::empty_dict, types::dict<K, V>const& b) -> decltype(b) {
                return b;
            }

        template <class A>
            auto iadd(types::empty_set, types::set<A> const& b) -> decltype(b) {
                return b;
            }
        PROXY(pythonic::operator_, iadd);

    }

}

#endif

