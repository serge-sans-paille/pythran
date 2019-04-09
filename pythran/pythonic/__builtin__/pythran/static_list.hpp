#ifndef PYTHONIC_BUILTIN_PYTHRAN_STATIC_LIST_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_STATIC_LIST_HPP

#include "pythonic/include/__builtin__/pythran/static_list.hpp"
#include "pythonic/__builtin__/list.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    template <class T, size_t N>
    types::static_list<T, N> static_list(types::array<T, N> const &other)
    {
      return other.template to_array<types::list_version>();
    }
    template <class T, size_t N>
    types::static_list<T, N> static_list(types::array<T, N> &other)
    {
      return other.template to_array<types::list_version>();
    }
    template <class T, size_t N>
    types::static_list<T, N> static_list(types::array<T, N> &&other)
    {
      return other.template to_array<types::list_version>();
    }

    template <class T>
    auto static_list(T &&other) -> decltype(
        pythonic::__builtin__::functor::list{}(std::forward<T>(other)))
    {
      return pythonic::__builtin__::functor::list{}(std::forward<T>(other));
    }
  }
}
PYTHONIC_NS_END

#endif
