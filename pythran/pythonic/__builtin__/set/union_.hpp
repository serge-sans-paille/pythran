#ifndef PYTHONIC_BUILTIN_SET_UNION_HPP
#define PYTHONIC_BUILTIN_SET_UNION_HPP

#include "pythonic/include/__builtin__/set/union_.hpp"

#include "pythonic/types/set.hpp"
#include "pythonic/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <typename T, typename... Types>
      typename __combined<types::set<T>, Types...>::type
      union_(types::set<T> const &set, Types const &... others)
      {
        return set.union_(others...);
      }

      template <typename... Types>
      typename __combined<types::empty_set, Types...>::type
      union_(types::empty_set const &init, Types const &... others)
      {
        return union_(others...);
      }

      template <typename T>
      types::set<T> union_(types::set<T> const &set)
      {
        return set;
      }

      template <typename T>
      typename __combined<types::empty_set, T>::type union_(T const &set)
      {
        return {set};
      }

      types::empty_set union_(types::empty_set const &init)
      {
        return types::empty_set();
      }

      DEFINE_FUNCTOR(pythonic::__builtin__::set, union_);
    }
  }
}
#endif
