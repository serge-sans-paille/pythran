#ifndef OPERATOR_NAME
#error OPERATOR_NAME not defined
#endif

#ifndef OPERATOR_SYMBOL
#error OPERATOR_SYMBOL not defined
#endif

#ifndef OPERATOR_ISYMBOL
#error OPERATOR_ISYMBOL not defined
#endif
#include "pythonic/utils/functor.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#endif

namespace pythonic
{

  namespace operator_
  {

#ifdef USE_BOOST_SIMD
    template <class T0, class T1, class T2, class B>
    auto OPERATOR_NAME(boost::simd::native<T0, T1, T2> &a, B &&b)
        -> decltype(a OPERATOR_ISYMBOL std::forward<B>(b))
    {
      return a OPERATOR_ISYMBOL std::forward<B>(b);
    }
    template <class T0, class T1, class T2, class B>
    auto OPERATOR_NAME(boost::simd::native<T0, T1, T2> &&a, B &&b)
        -> decltype(a OPERATOR_ISYMBOL std::forward<B>(b))
    {
      return a OPERATOR_ISYMBOL std::forward<B>(b);
    }
    template <class A, class T0, class T1, class T2>
    auto OPERATOR_NAME(A &&a, boost::simd::native<T0, T1, T2> &b)
        -> decltype(std::forward<A>(a) OPERATOR_ISYMBOL b)
    {
      return std::forward<A>(a) OPERATOR_ISYMBOL b;
    }
    template <class A, class T0, class T1, class T2>
    auto OPERATOR_NAME(A &&a, boost::simd::native<T0, T1, T2> &&b)
        -> decltype(std::forward<A>(a) OPERATOR_ISYMBOL b)
    {
      return std::forward<A>(a) OPERATOR_ISYMBOL b;
    }

    template <class P0, class P1, class P2, class T0, class T1, class T2>
    auto OPERATOR_NAME(boost::simd::native<P0, P1, P2> &a,
                       boost::simd::native<T0, T1, T2> &b)
        -> decltype(a OPERATOR_ISYMBOL b)
    {
      return a OPERATOR_ISYMBOL b;
    }
    template <class P0, class P1, class P2, class T0, class T1, class T2>
    auto OPERATOR_NAME(boost::simd::native<P0, P1, P2> &&a,
                       boost::simd::native<T0, T1, T2> &b)
        -> decltype(a OPERATOR_ISYMBOL b)
    {
      return a OPERATOR_ISYMBOL b;
    }
    template <class P0, class P1, class P2, class T0, class T1, class T2>
    auto OPERATOR_NAME(boost::simd::native<P0, P1, P2> &a,
                       boost::simd::native<T0, T1, T2> &&b)
        -> decltype(a OPERATOR_ISYMBOL b)
    {
      return a OPERATOR_ISYMBOL b;
    }
    template <class P0, class P1, class P2, class T0, class T1, class T2>
    auto OPERATOR_NAME(boost::simd::native<P0, P1, P2> &&a,
                       boost::simd::native<T0, T1, T2> &&b)
        -> decltype(a OPERATOR_ISYMBOL b)
    {
      return a OPERATOR_ISYMBOL b;
    }
#endif

    template <class A, class B>
    auto OPERATOR_NAME(A &&a, B &&b) -> typename std::enable_if<
        std::is_const<A>::value or not std::is_assignable<A, B>::value,
        decltype(std::forward<A>(a) OPERATOR_SYMBOL std::forward<B>(b))>::type
    {
      return std::forward<A>(a) OPERATOR_SYMBOL std::forward<B>(b);
    }
    template <class A, class B>
    auto OPERATOR_NAME(A &&a, B &&b) -> typename std::enable_if<
        not std::is_const<A>::value and std::is_assignable<A, B>::value,
        decltype(std::forward<A>(a) OPERATOR_ISYMBOL std::forward<B>(b))>::type
    {
      return std::forward<A>(a) OPERATOR_ISYMBOL std::forward<B>(b);
    }

    DEFINE_FUNCTOR(pythonic::operator_, OPERATOR_NAME);
  }
}
#undef OPERATOR_NAME
#undef OPERATOR_SYMBOL
#undef OPERATOR_ISYMBOL
