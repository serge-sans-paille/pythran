#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_UNION_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_UNION_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <typename T, typename... Types>
      typename __combined<types::set<T>, Types...>::type
      union_(types::set<T> const &set, Types const &... others);

      template <typename... Types>
      typename __combined<types::empty_set, Types...>::type
      union_(types::empty_set const &init, Types const &... others);

      template <typename T>
      types::set<T> union_(types::set<T> const &set);

      template <typename T>
      typename __combined<types::empty_set, T>::type union_(T const &set);

      types::empty_set union_(types::empty_set const &init);

      PROXY_DECL(pythonic::builtins::set, union_);
    }
  }
}
#endif
