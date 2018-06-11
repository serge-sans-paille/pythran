#ifndef PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATICIFRETURN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_PYTHRAN_STATICIFRETURN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/attr.hpp"
#include "pythonic/include/types/tuple.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  struct StaticIfReturn {
    T arg;
  };
  template <class T0, class T1>
  struct StaticIfReturnHolder {
    std::tuple<bool, T0, T1> args;

    StaticIfReturnHolder(StaticIfReturnHolder<T0, T1> const &) = default;

    template <class Tp0, class Tp1>
    StaticIfReturnHolder(StaticIfReturnHolder<Tp0, Tp1> const &other)
        : args(other.args)
    {
    }

    StaticIfReturnHolder(StaticIfReturn<T0> const &arg)
        : args(true, arg.arg, T1())
    {
    }
    StaticIfReturnHolder(T1 const &arg) : args(false, T0(), arg)
    {
    }
  };
}

namespace __builtin__
{

  namespace pythran
  {
    template <class T>
    types::StaticIfReturn<T> StaticIfReturn(T const &arg);

    DECLARE_FUNCTOR(pythonic::__builtin__::pythran, StaticIfReturn);
  }
}
PYTHONIC_NS_END

namespace std
{
  template <size_t I, class T0, class T1>
  struct tuple_element<I, pythonic::types::StaticIfReturnHolder<T0, T1>> {
    using type = typename std::conditional<
        I == 0, bool, typename std::conditional<I == 1, T0, T1>::type>::type;
  };
  template <size_t I, class T0, class T1>
  auto get(pythonic::types::StaticIfReturnHolder<T0, T1> &t)
      -> decltype(std::get<I>(t.args))
  {
    return std::get<I>(t.args);
  }
}
template <class T, class Ty, size_t N>
struct __combined<pythonic::types::array<Ty, N>,
                  pythonic::types::StaticIfReturn<T>> {
  using type =
      pythonic::types::StaticIfReturnHolder<T, pythonic::types::array<Ty, N>>;
};

template <class T, class Ty, size_t N>
struct __combined<pythonic::types::StaticIfReturn<T>,
                  pythonic::types::array<Ty, N>> {
  using type =
      pythonic::types::StaticIfReturnHolder<T, pythonic::types::array<Ty, N>>;
};

template <class T, class... Tys>
struct __combined<pythonic::types::StaticIfReturn<T>, std::tuple<Tys...>> {
  using type = pythonic::types::StaticIfReturnHolder<T, std::tuple<Tys...>>;
};

template <class T, class... Tys>
struct __combined<std::tuple<Tys...>, pythonic::types::StaticIfReturn<T>> {
  using type = pythonic::types::StaticIfReturnHolder<T, std::tuple<Tys...>>;
};

template <class T0, class T1, class T2>
struct __combined<pythonic::types::StaticIfReturnHolder<T0, T1>, T2> {
  using type =
      pythonic::types::StaticIfReturnHolder<T0,
                                            typename __combined<T1, T2>::type>;
};

template <class T0, class T1, class T2>
struct __combined<T2, pythonic::types::StaticIfReturnHolder<T0, T1>> {
  using type =
      pythonic::types::StaticIfReturnHolder<T0,
                                            typename __combined<T1, T2>::type>;
};
template <class T0, class T1, class T2, class T3>
struct __combined<pythonic::types::StaticIfReturnHolder<T0, T1>,
                  pythonic::types::StaticIfReturnHolder<T2, T3>> {
  using type =
      pythonic::types::StaticIfReturnHolder<typename __combined<T0, T2>::type,
                                            typename __combined<T1, T3>::type>;
};
template <class T0, class T1, class T2>
struct __combined<pythonic::types::StaticIfReturnHolder<T0, T1>,
                  pythonic::types::StaticIfReturn<T2>> {
  using type =
      pythonic::types::StaticIfReturnHolder<typename __combined<T0, T2>::type,
                                            T1>;
};
template <class T0, class T1, class T2>
struct __combined<pythonic::types::StaticIfReturn<T2>,
                  pythonic::types::StaticIfReturnHolder<T0, T1>> {
  using type =
      pythonic::types::StaticIfReturnHolder<typename __combined<T0, T2>::type,
                                            T1>;
};

#endif
