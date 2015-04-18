#ifndef PYTHONIC_INCLUDE_BUILTIN_STR_JOIN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_STR_JOIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace str {

            template <class S>
                types::str join(S const &s, types::str const& iterable);

            template <class S, class Iterable>
                typename std::enable_if<
                    not std::is_same<
                        typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type,
                        types::str
                        >::value and
                    std::is_same<
                        typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                        std::random_access_iterator_tag
                        >::value,
                types::str
                    >::type
                join(S const &s, Iterable &&iterable);

            template<class S, class Iterable>
                typename std::enable_if<
                    not std::is_same<
                        typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                         std::random_access_iterator_tag
                         > :: value,
                     types::str
                     >::type
                 join(S const &s, Iterable &&iterable);

            PROXY_DECL(pythonic::__builtin__::str, join);

        }

    }

}
#endif
