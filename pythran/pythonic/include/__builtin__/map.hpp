#ifndef PYTHONIC_INCLUDE_BUILTIN_MAP_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MAP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/NoneType.hpp"
#include "pythonic/include/types/tuple.hpp"

#include <utility>

namespace pythonic
{

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
      types::list<
          typename std::remove_reference<List0>::type::iterator::value_type>
      map(types::none_type, List0 &&seq);
    }

    template <typename Operator, typename List0, typename... ListN>
    auto map(Operator op, List0 &&seq, ListN &&... lists)
        -> decltype(details::map(op, std::forward<List0>(seq),
                                 lists.begin()...));

    DECLARE_FUNCTOR(pythonic::__builtin__, map);
  }
}

#endif
