//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_MAKE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_MAKE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief make generic tag

     Represents the make function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct make_ : ext::elementwise_<make_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<make_> parent;
    };
  }
} }

namespace boost { namespace dispatch
{
  /* We specialize functor directly due to arity limitations, and we only dispatch on the target.
   * We also avoid having to dispatch return type deduction, and we cast all arguments to the scalar
   * matching the target. */
  template<class Site>
  struct functor<boost::simd::tag::make_, Site>
  {
    template<class Sig>
    struct result;

    #define M1(z,n,t) static_cast<typename meta::scalar_of<typename Target::type>::type>(a##n)

    #define M0(z,n,t)                                                                      \
    template<class This, BOOST_PP_ENUM_PARAMS(n, class A), class Target>                   \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A), Target)>                                \
      : meta::strip<Target>::type                                                          \
    {                                                                                      \
    };                                                                                     \
                                                                                           \
    template<BOOST_PP_ENUM_PARAMS(n, class A), class Target>                               \
    typename Target::type BOOST_FORCEINLINE                                                \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a), Target const&) const           \
    {                                                                                      \
      typename meta::dispatch_call<boost::simd::tag::make_(Target), Site>::type callee;    \
      return callee(BOOST_PP_ENUM(n, M1, ~));                                              \
    }

    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
    #undef M1
  };
} }

namespace boost { namespace simd
{
  #define M0(z,n,t)                                                                        \
  template<class T, BOOST_PP_ENUM_PARAMS(n, class A)> BOOST_FORCEINLINE                    \
  T make(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                                      \
  {                                                                                        \
    typename boost::dispatch::make_functor<tag::make_, T>::type callee;                    \
    return callee(BOOST_PP_ENUM_PARAMS(n, a), boost::dispatch::meta::as_<T>());            \
  }

  BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
  #undef M0
} }

#endif
