#ifndef PYTHONIC_OPERATOR_IADD_HPP
#define PYTHONIC_OPERATOR_IADD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/set.hpp"
#include "pythonic/types/dict.hpp"

namespace pythonic {

    namespace operator_ {

        namespace proxy {

          struct iadd {
            template <class A, class B>
              auto operator()(A const & a, B&& b) -> decltype(a + std::forward<B>(b))
              {
                return a + std::forward<B>(b);
              }
            template <class A, class B>
                auto operator()(A& a, B && b) -> decltype(a+= std::forward<B>(b))
                {
                    return a+= std::forward<B>(b);
                }

            template <class A>
                auto operator()(types::empty_list, types::list<A> const& b) -> decltype(b) {
                    return b;
                }

            template <class K, class V>
                auto operator()(types::empty_dict, types::dict<K, V>const& b) -> decltype(b) {
                    return b;
                }

            template <class A>
                auto operator()(types::empty_set, types::set<A> const& b) -> decltype(b) {
                    return b;
                }
          };
        }

        template<class A, class B>
        auto iadd(A&& a, B&& b) -> decltype(proxy::iadd{}(std::forward<A>(a), std::forward<B>(b)))
        {
          return proxy::iadd{}(std::forward<A>(a), std::forward<B>(b));
        }

    }

}

#endif

