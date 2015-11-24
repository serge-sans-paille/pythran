#ifndef PYTHONIC_UTILS_FUNCTOR_HPP
#define PYTHONIC_UTILS_FUNCTOR_HPP

#include "pythonic/include/utils/functor.hpp"

#include <utility>

#define DEFINE_FUNCTOR_2(s, f)                                                 \
  namespace functor                                                            \
  {                                                                            \
    template <typename... Types>                                               \
    auto s::operator()(Types && ... types) const                               \
        -> decltype(f(std::forward<Types>(types)...))                          \
    {                                                                          \
      return f(std::forward<Types>(types)...);                                 \
    }                                                                          \
  }

// create a functor named `f' using function `ns::f'
#define DEFINE_FUNCTOR(ns, f) DEFINE_FUNCTOR_2(f, ns::f)

#endif
