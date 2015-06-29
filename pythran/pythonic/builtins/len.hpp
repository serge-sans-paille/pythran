#ifndef PYTHONIC_BUILTIN_LEN_HPP
#define PYTHONIC_BUILTIN_LEN_HPP

#include "pythonic/include/builtins/len.hpp"

#include "pythonic/types/traits.hpp"
#include "pythonic/utils/proxy.hpp"

#include <tuple>
#include <iterator>

namespace pythonic
{

  namespace builtins
  {
    template <class... Types>
    long len(std::tuple<Types...> const &)
    {
      return sizeof...(Types);
    }

    constexpr long len(char)
    {
      return 1;
    }

    template <class T>
    typename std::enable_if<types::has_size<T>::value, long>::type
    len(T const &t)
    {
      return t.size();
    }

    template <class T>
    typename std::enable_if<not types::has_size<T>::value, long>::type
    len(T const &t)
    {
      static_assert(
          std::is_same<typename std::iterator_traits<
                           typename T::iterator>::iterator_category,
                       std::random_access_iterator_tag>::value,
          "distance is not really efficient without random iterators...");
      return std::distance(t.begin(), t.end());
    }

    PROXY_IMPL(pythonic::builtins, len);
  }
}
#endif
