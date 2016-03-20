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

namespace pythonic
{

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
          -> types::list<decltype(types::make_tuple(*seq.begin(),
                                                    *iterators...))>
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
      types::list<
          typename std::remove_reference<List0>::type::iterator::value_type>
      map(types::none_type, List0 &&seq)
      {
        types::list<typename std::remove_reference<
            List0>::type::iterator::value_type> s(0);
        utils::reserve(s, seq);
        for (auto const &iseq : seq)
          s.push_back(iseq);
        return s;
      }
    }

    template <typename Operator, typename List0, typename... ListN>
    auto map(Operator op, List0 &&seq, ListN &&... lists)
        -> decltype(details::map(op, std::forward<List0>(seq),
                                 lists.begin()...))
    {
      return details::map(op, std::forward<List0>(seq), lists.begin()...);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__, map);
  }
}

#endif
