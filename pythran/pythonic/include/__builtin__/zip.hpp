#ifndef PYTHONIC_INCLUDE_BUILTIN_ZIP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ZIP_HPP

#include "pythonic/types/list.hpp"
#include "pythonic/types/tuple.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace __builtin__ {

        template<class Iterator0, class... Iterators>
            types::list<std::tuple<typename Iterator0::value_type, typename Iterators::value_type... > >
            _zip(size_t n, Iterator0 first, Iterators...  iters);

        template<class List0, class... Lists>
            types::list<std::tuple<typename std::remove_reference<List0>::type::value_type, typename std::remove_reference<Lists>::type::value_type... > >
            zip(List0 && s0, Lists &&...  lists);

        types::empty_list zip();

        PROXY_DECL(pythonic::__builtin__,zip);

    }

}

#endif
