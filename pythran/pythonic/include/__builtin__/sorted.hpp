#ifndef PYTHONIC_INCLUDE_BUILTIN_SORTED_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SORTED_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

namespace pythonic {

    namespace __builtin__ {

        template <class Iterable>
            types::list<typename std::remove_cv<typename Iterable::iterator::value_type>::type>
            sorted(Iterable const& seq);

        template <class Iterable, class C>
            types::list<typename std::remove_cv<typename Iterable::iterator::value_type>::type>
            sorted(Iterable const& seq, C const& cmp);

        PROXY_DECL(pythonic::__builtin__, sorted);

    }

}

#endif
