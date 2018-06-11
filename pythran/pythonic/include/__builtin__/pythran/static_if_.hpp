#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATIC_IF_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATIC_IF_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/__builtin__/pythran/is_none.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class F0, class F1>
  struct static_if_return {
    F0 f0;
    static_if_return(F0 const &f0) : f0(f0)
    {
    }

    template <class... Args>
    using result_type = typename __combined<
        decltype(F0{}(std::forward<Args>(std::declval<Args>())...)),
        decltype(F1{}(std::forward<Args>(std::declval<Args>())...))>::type;

    template <class... Args>
    result_type<Args...> operator()(Args &&... args)
    {
      return result_type<Args...>(f0(std::forward<Args>(args)...));
    }
  };
}

namespace __builtin__
{

  namespace pythran
  {
    template <class T, class F0, class F1>
    typename std::conditional<std::is_same<T, types::true_type>::value,
                              types::static_if_return<F0, F1>,
                              types::static_if_return<F1, F0>>::type
    static_if_(T const &cond, F0 f0, F1 f1);

    DECLARE_FUNCTOR(pythonic::__builtin__::pythran, static_if_);
  }
}
PYTHONIC_NS_END

#endif
