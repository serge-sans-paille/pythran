#ifndef PYTHONIC_BUILTIN_MAP_HPP
#define PYTHONIC_BUILTIN_MAP_HPP

#include "pythonic/include/__builtin__/map.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/types/NoneType.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/fwd.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/reserve.hpp"

#include <utility>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace details
  {
    template <typename Operator, typename List0, typename... Iterators>
    auto map(Operator &op, List0 &&seq, Iterators... iterators)
        -> types::list<decltype(op(*seq.begin(), *iterators...))>
    {
      types::list<decltype(op(*seq.begin(), *iterators...))> s(0);
      utils::reserve(s, seq);
      for (auto const &iseq : seq) {
        s.push_back(op(iseq, *iterators...));
        utils::fwd(++iterators...);
      }
      return s;
    }

    template <typename List0, typename... Iterators>
    auto map(types::none_type, List0 &&seq, Iterators... iterators)
        -> types::list<decltype(types::make_tuple(*seq.begin(), *iterators...))>
    {
      types::list<decltype(types::make_tuple(*seq.begin(), *iterators...))> s(
          0);
      utils::reserve(s, seq);
      for (auto const &iseq : seq) {
        s.push_back(types::make_tuple(iseq, *iterators...));
        utils::fwd(++iterators...);
      }
      return s;
    }

    template <typename List0>
    types::list<typename std::iterator_traits<
        typename std::remove_reference<List0>::type::iterator>::value_type>
    map(types::none_type, List0 &&seq)
    {
      types::list<typename std::iterator_traits<typename std::remove_reference<
          List0>::type::iterator>::value_type> s(0);
      utils::reserve(s, seq);
      for (auto const &iseq : seq)
        s.push_back(iseq);
      return s;
    }

    template <long N, typename Operator, typename List0, typename... ListN>
    auto mapN(Operator &op, List0 &&seq, ListN &&... lists)
        -> types::static_list<decltype(op(*seq.begin(), *lists.begin()...)), N>
    {
      types::static_list<decltype(op(*seq.begin(), *lists.begin()...)), N> s;
      for (long i = 0; i < N; ++i)
        s[i] = op(*(seq.begin() + i), (*(lists.begin() + i))...);
      return s;
    }

    template <long N, typename List0, typename... ListN>
    auto mapN(types::none_type, List0 &&seq, ListN &&... lists)
        -> types::static_list<
            decltype(types::make_tuple(*seq.begin(), *lists.begin()...)), N>
    {
      types::static_list<
          decltype(types::make_tuple(*seq.begin(), *lists.begin()...)), N> s;
      for (long i = 0; i < N; ++i)
        s[i] = types::make_tuple(seq[i], lists[i]...);
      return s;
    }
  }

  template <typename Operator, typename List0, typename... ListN>
  auto map(Operator op, List0 &&seq, ListN &&... lists) ->
      typename std::enable_if<
          !utils::all_of<
              types::len_of<typename std::decay<List0>::type>::value != -1,
              (types::len_of<typename std::decay<ListN>::type>::value !=
               -1)...>::value,
          decltype(details::map(op, std::forward<List0>(seq),
                                lists.begin()...))>::type
  {
    return details::map(op, std::forward<List0>(seq), lists.begin()...);
  }

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
              std::forward<ListN>(lists)...))>::type
  {
    return details::mapN<
        types::len_of<typename std::decay<List0>::type>::value>(
        op, std::forward<List0>(seq), lists.begin()...);
  }
}
PYTHONIC_NS_END

#endif
