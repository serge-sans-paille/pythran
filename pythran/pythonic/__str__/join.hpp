#ifndef PYTHONIC_STR_JOIN_HPP
#define PYTHONIC_STR_JOIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/len.hpp"

namespace pythonic {

    namespace __str__ {
        template<class Iterable>
            typename std::enable_if<
            std::is_same<
            typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                     std::random_access_iterator_tag
                         > :: value,
                     types::str
                         >::type
                         join(types::str const & s, Iterable && iterable) {
                             /* first iterate over iterable to gather sizes */
                             size_t n = s.size() * std::distance(iterable.begin(), iterable.end());
                             for(auto const& iter:iterable)
                                 n += __builtin__::len(iter);

                             types::str out("");
                             out.reserve(n);

                             auto iter = iterable.begin();
                             if(iter != iterable.end()) {
                                 out += *iter;
                                 ++iter;
                                 for(;iter!=iterable.end();++iter) {
                                     out += s ;
                                     out += *iter ;
                                 }
                             }
                             return out;
                         }

        template<class Iterable>
            typename std::enable_if<
            not std::is_same<
            typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                     std::random_access_iterator_tag
                         > :: value,
                     types::str
                         >::type
                         join(types::str const & s, Iterable && iterable) {

                             types::str out;
                             auto iter = iterable.begin();
                             if(iter != iterable.end()) {
                                 out += *iter;
                                 ++iter;
                                 for(;iter!=iterable.end();++iter) {
                                     out += s ;
                                     out += *iter ;
                                 }
                             }
                             return out;
                         }
        PROXY(pythonic::__str__, join);

    }

}

#endif

