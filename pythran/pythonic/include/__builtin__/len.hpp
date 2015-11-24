#ifndef PYTHONIC_INCLUDE_BUILTIN_LEN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LEN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/yield.hpp"

#include <tuple>
#include <iterator>

namespace pythonic
{

  namespace __builtin__
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

    DECLARE_FUNCTOR(pythonic::__builtin__, len);
  }
}
#endif
