#ifndef PYTHONIC_OPERATOR_ICONCAT_HPP
#define PYTHONIC_OPERATOR_ICONCAT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/set.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            A iconcat(A  a, B const& b) {
                return a+=b;
            }

        template <class A>
            auto iconcat(types::empty_list a, types::list<A> b) -> decltype(b) {
                return b;
            }

        template <class K, class V>
            auto iconcat(types::empty_dict a, types::dict<K, V> b) -> decltype(b) {
                return b;
            }

        template <class A>
            auto iconcat(types::empty_set a, types::set<A> b) -> decltype(b) {
                return b;
            }
        PROXY(pythonic::operator_, iconcat);

    }

}

#endif

