#ifndef PYTHONIC_BUILTIN_PYTHRAN_STATIC_IF_HPP
#define PYTHONIC_BUILTIN_PYTHRAN_STATIC_IF_HPP

#include "pythonic/include/__builtin__/pythran/static_if_.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/__builtin__/pythran/is_none.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace pythran
  {
    namespace details
    {
      template <class IsSame>
      struct static_if_;

      template <>
      struct static_if_<types::true_type> {
        template <class F0, class F1>
        F0 operator()(F0 f0, F1 f1)
        {
          return f0;
        }
      };
      template <>
      struct static_if_<types::false_type> {
        template <class F0, class F1>
        F1 operator()(F0 f0, F1 f1)
        {
          return f1;
        }
      };
    }

    template <class T, class F0, class F1>
    typename std::conditional<std::is_same<T, types::true_type>::value, F0,
                              F1>::type
    static_if_(T const &cond, F0 f0, F1 f1)
    {
      return details::static_if_<T>{}(f0, f1);
    }
  }
}
PYTHONIC_NS_END

#endif
