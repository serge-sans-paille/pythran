#ifndef PYTHONIC_INCLUDE_BUILTIN_LEN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LEN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/utils/yield.hpp"

#include <tuple>
#include <iterator>

namespace pythonic
{

  namespace builtins
  {

    template <class... Types>
    long len(std::tuple<Types...> const &);

    constexpr long len(char);

    template <class T>
    typename std::enable_if<types::has_size<T>::value, long>::type
    len(T const &t);

    template <class T>
    typename std::enable_if<not types::has_size<T>::value, long>::type
    len(T const &t);

    PROXY_DECL(pythonic::builtins, len);
  }
}
#endif
