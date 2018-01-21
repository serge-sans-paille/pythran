#ifndef PYTHONIC_BUILTIN_PRINT_HPP
#define PYTHONIC_BUILTIN_PRINT_HPP

#include "pythonic/include/__builtin__/print.hpp"
#include "pythonic/utils/functor.hpp"

#include <iostream>

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace details
  {
    template <class T>
    std::ostream &print(std::ostream &os, T const &t)
    {
      return os << t;
    }

    std::ostream &print(std::ostream &os, bool const &t)
    {
      static char const repr[2][6] = {"False", "True\0"};
      return os << repr[t];
    }
  }

  void print_nonl()
  {
  }

  template <typename T, typename... Types>
  void print_nonl(T const &value, Types const &... values)
  {
    details::print(std::cout, value);
    if (sizeof...(Types) > 0)
      std::cout << ' ';
    print_nonl(values...);
  }

  void print()
  {
    std::cout << std::endl;
  }

  template <typename T, typename... Types>
  void print(T const &value, Types const &... values)
  {
    details::print(std::cout, value);
    if (sizeof...(values) > 0)
      std::cout << ' ';
    print(values...);
  }
  DEFINE_FUNCTOR(pythonic::__builtin__, print);
}
PYTHONIC_NS_END

#endif
