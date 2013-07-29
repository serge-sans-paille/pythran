#ifndef PYTHONIC_BUILTIN_MAP_HPP
#define PYTHONIC_BUILTIN_MAP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/fwd.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/__builtin__/len.hpp"
#include "pythonic/types/tuple.hpp"

#include <utility>

namespace pythonic {

    namespace __builtin__ {

        template <typename Operator, typename List0, typename... Iterators>
            auto _map(Operator& op, List0 && seq, Iterators... iterators)
            -> types::list< decltype(op(*seq.begin(), *iterators...)) > 
            {
                types::list< decltype(op(*seq.begin(), *iterators...)) > s(0);
                s.reserve(len(seq));
                for(auto const& iseq : seq) {
                    s.push_back(op(iseq, *iterators...));
                    utils::fwd(++iterators...);
                }
                return s;
            }


        template <typename List0, typename... Iterators>
            auto _map(types::none_type, List0 && seq, Iterators... iterators) 
            -> types::list< std::tuple< typename std::remove_reference<List0>::type::iterator::value_type,  typename Iterators::value_type... > >
            {
                types::list< std::tuple< typename std::remove_reference<List0>::type::iterator::value_type,  typename Iterators::value_type... > > s(0);
                s.reserve(len(seq));
                for(auto const& iseq : seq) {
                    s.push_back(std::make_tuple( iseq, *iterators... ));
                    utils::fwd(++iterators...);
                }
                return s;
            }

        template <typename List0>
            auto _map(types::none_type, List0 && seq)
            -> types::list< typename std::remove_reference<List0>::type::iterator::value_type >
            {
                types::list< typename std::remove_reference<List0>::type::iterator::value_type > s(0);
                s.reserve(len(seq));
                for(auto const& iseq : seq)
                    s.push_back(iseq);
                return s;
            }

        template <typename Operator, typename List0, typename... ListN>
            auto map(Operator op, List0 && seq, ListN &&... lists)
            -> decltype( _map(op, std::forward<List0>(seq), lists.begin()...) )
            {
                return _map(op, std::forward<List0>(seq), lists.begin()...);
            }

        PROXY(pythonic::__builtin__,map);

    }

}

#endif
