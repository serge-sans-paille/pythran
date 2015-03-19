#ifndef PYTHONIC_INCLUDE_BUILTIN_MAP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MAP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/tuple.hpp"

#include <utility>

namespace pythonic {

    namespace __builtin__ {

        template <typename Operator, typename List0, typename... Iterators>
            auto _map(Operator& op, List0 && seq, Iterators... iterators)
            -> types::list< decltype(op(*seq.begin(), *iterators...)) >;

        template <typename List0, typename... Iterators>
            types::list< std::tuple< typename std::remove_reference<List0>::type::iterator::value_type,  typename Iterators::value_type... > >
            _map(types::none_type, List0 && seq, Iterators... iterators);

        template <typename List0>
            types::list< typename std::remove_reference<List0>::type::iterator::value_type >
            _map(types::none_type, List0 && seq);

        template <typename Operator, typename List0, typename... ListN>
            auto map(Operator op, List0 && seq, ListN &&... lists)
            -> decltype( _map(op, std::forward<List0>(seq), lists.begin()...) );

        PROXY_DECL(pythonic::__builtin__,map);

    }

}

#endif
