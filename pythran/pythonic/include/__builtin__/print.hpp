#ifndef PYTHONIC_INCLUDE_BUILTIN_PRINT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PRINT_HPP

#include <ostream>

namespace pythonic
{

  namespace __builtin__
  {

    namespace details
    {
      template <class T>
      std::ostream &print(std::ostream &os, T const &t);
    }

    void print_nonl();

    template <typename T, typename... Types>
    void print_nonl(T const &value, Types const &... values);

    void print();

    template <typename T, typename... Types>
    void print(T const &value, Types const &... values);
  }
}

#endif
