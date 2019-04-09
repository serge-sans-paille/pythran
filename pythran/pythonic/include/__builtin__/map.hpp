#ifndef PYTHONIC_INCLUDE_BUILTIN_MAP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MAP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/tuple.hpp"

#include <utility>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace details
  {
    template <typename Operator, typename List0, typename... Iterators>
    auto map(Operator &op, List0 &&seq, Iterators... iterators)
        -> types::list<decltype(op(*seq.begin(), *iterators...))>;

    template <typename List0, typename... Iterators>
    auto map(types::none_type, List0 &&seq, Iterators... iterators)
        -> types::list<decltype(types::make_tuple(*seq.begin(),
                                                  *iterators...))>;

    template <typename List0>
    types::list<typename std::iterator_traits<
        typename std::remove_reference<List0>::type::iterator>::value_type>
    map(types::none_type, List0 &&seq);

    template <long N, typename Operator, typename List0, typename... ListN>
    auto mapN(Operator &op, List0 &&seq, ListN &&... lists)
        -> types::static_list<decltype(op(*seq.begin(), *lists.begin()...)), N>;

    template <long N, typename List0, typename... ListN>
    auto mapN(types::none_type, List0 &&seq, ListN &&... lists)
        -> types::static_list<
            decltype(types::make_tuple(*seq.begin(), *lists.begin()...)), N>;
  }

  template <typename Operator, typename List0, typename... ListN>
  auto map(Operator op, List0 &&seq, ListN &&... lists) ->
      typename std::enable_if<
          !utils::all_of<
              types::len_of<typename std::decay<List0>::type>::value != -1,
              (types::len_of<typename std::decay<ListN>::type>::value !=
               -1)...>::value,
          decltype(details::map(op, std::forward<List0>(seq),
                                lists.begin()...))>::type;

  template <typename Operator, typename List0, typename... ListN>
  auto map(Operator op, List0 &&seq, ListN &&... lists) ->
      typename std::enable_if<
          utils::all_of<
              types::len_of<typename std::decay<List0>::type>::value != -1,
              (types::len_of<typename std::decay<ListN>::type>::value !=
               -1)...>::value,
          decltype(details::mapN<
              types::len_of<typename std::decay<List0>::type>::value>(
              op, std::forward<List0>(seq),
              std::forward<ListN>(lists)...))>::type;

  DEFINE_FUNCTOR(pythonic::__builtin__, map);
}
PYTHONIC_NS_END

#endif
