#ifndef PYTHONIC_INCLUDE_BUILTIN_ISINSTANCE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ISINSTANCE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/builtins/pythran/is_none.hpp"

PYTHONIC_NS_BEGIN
namespace types
{
  struct str;

  template <class Ty0, class Ty1>
  struct isinstance
      : std::conditional<std::is_same<Ty0, Ty1>::value, true_type, false_type> {
  };

  // some specialization

  template <>
  struct isinstance<char const *, str> {
    using type = true_type;
  };
  template <>
  struct isinstance<str, char const *> {
    using type = true_type;
  };
}

namespace builtins
{
  template <class Obj, class Cls>
  typename types::isinstance<
      Obj, typename std::decay<decltype(std::declval<Cls>()())>::type>::type
      isinstance(Obj, Cls)
  {
    return {};
  }

  DEFINE_FUNCTOR(pythonic::builtins, isinstance);
}
PYTHONIC_NS_END

#endif
