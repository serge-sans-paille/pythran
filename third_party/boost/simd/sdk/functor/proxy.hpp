//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_FUNCTOR_PROXY_HPP_INCLUDED
#define BOOST_SIMD_SDK_FUNCTOR_PROXY_HPP_INCLUDED

#include <boost/dispatch/meta/any.hpp>
#include <boost/dispatch/meta/proxy.hpp>
#include <boost/dispatch/meta/unproxy.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/selection/min.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( unspecified_<Func>, tag::cpu_
                                    , (Func)(A0)
                                    , (proxy_<A0>)
                                    )
  {
    typedef typename dispatch::meta::unproxy<A0>::type              b0_t;
    typedef typename dispatch::meta::call<Func(b0_t const&)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typename dispatch::make_functor<Func,A0>::type callee;
      return callee( dispatch::unproxy(a0) );
    }
  };

  #define M0(z,n,t) (A##n)
  /**/
  #define M1(z,n,t) (unspecified_<A##n>)
  /**/
  #define M2(z,n,t)                                                           \
  typedef typename boost::dispatch::meta::                                    \
          unproxy< typename boost::remove_reference<_A##n>::type >::type      \
  b##n##_t;                                                                   \
  /**/
  #define M3(z,n,t) b##n##_t
  /**/
  #define M4(z,n,t) boost::dispatch::unproxy(a##n)
  /**/

  #define M5(z,n,t)                                                           \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( unspecified_<Func>, tag::cpu_         \
                                      , (Func)BOOST_PP_REPEAT(n,M0,~)         \
                                      , ( meta::any                           \
                                          < meta::is_proxy<boost::mpl::_>     \
                                          , BOOST_PP_ENUM_PARAMS(n,A)         \
                                          >                                   \
                                        )                                     \
                                      , BOOST_PP_REPEAT(n,M1,~)               \
                                      )                                       \
  {                                                                           \
    template<class Sig>                                                       \
    struct result;                                                            \
                                                                              \
    template<class This, BOOST_PP_ENUM_PARAMS(n, class _A)>                   \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, _A))>                          \
    {                                                                         \
      BOOST_PP_REPEAT(n,M2,~)                                                 \
      typedef typename dispatch::meta::call                                   \
              <Func(BOOST_PP_ENUM(n,M3,~))>::type type;                       \
    };                                                                        \
                                                                              \
    template<BOOST_PP_ENUM_PARAMS(n, class _A)>                               \
    BOOST_FORCEINLINE                                                         \
    typename result<implement(BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & BOOST_PP_INTERCEPT))>::type \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & a)) const                 \
    {                                                                         \
      typename dispatch::make_functor<Func, _A0>::type callee;                \
      return callee ( BOOST_PP_ENUM(n,M4,~) );                                \
    }                                                                         \
  };                                                                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO ( 2
                          , BOOST_PP_INC(BOOST_PP_MIN ( BOOST_DISPATCH_MAX_ARITY
                                                      , BOOST_PROTO_MAX_ARITY
                                                      )
                                        )
                          , M5 ,~
                          )

  #undef M0
  #undef M1
  #undef M2
  #undef M3
  #undef M4
  #undef M5
} } }

#endif
