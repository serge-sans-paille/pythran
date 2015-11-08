//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_AGGREGATE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_AGGREGATE_HPP_INCLUDED

#include <nt2/core/functions/aggregate.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace ext
{
#define M0(z,n,t) (A##n)
#define M1(z,n,t) (unspecified_<A##n>)
#define M2(z,n,t) boost::cref(a##n)

#define M3(z,n,t)                                                             \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::aggregate_, tag::cpu_                   \
                          , BOOST_PP_REPEAT(n,M0,~)                           \
                          , BOOST_PP_REPEAT(n,M1,~)                           \
                          )                                                   \
{                                                                             \
  typedef typename  boost::proto::result_of::make_expr                        \
                    < nt2::tag::aggregate_, container::domain                 \
                    , BOOST_PP_ENUM_BINARY_PARAMS ( n                         \
                                                  , const A                   \
                                                  , & BOOST_PP_INTERCEPT)     \
                    >::type      result_type;                                 \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a) ) const               \
  {                                                                           \
    return boost::proto::make_expr<tag::aggregate_,container::domain>         \
                                  ( BOOST_PP_ENUM(n,M2,~) );                  \
  }                                                                           \
};                                                                            \
/**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M3,~)

#undef M0
#undef M1
#undef M2
#undef M3
} }

#endif
