//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_VALUE_ELEMENTWISE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_VALUE_ELEMENTWISE_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // default value_type, calls meta::call on the scalar equivalent. This is the
  // case for both element-wise and reduction expression
  //============================================================================
  #define M1(z,n,t)                                                         \
  typedef typename boost::proto::result_of::child_c<Expr&, n>::type _A##n;  \
  typedef typename boost::dispatch::meta::semantic_of<_A##n>::type A##n;    \
  typedef typename boost::dispatch::meta::scalar_of<A##n>::type s##n;       \
  /**/

  #define M0(z,n,t)                                                         \
  template<class F, class Domain, class Expr>                               \
  struct value_type<F, Domain, n, Expr>                                     \
  {                                                                         \
    BOOST_PP_REPEAT(n, M1, ~)                                               \
    typedef typename meta::call<F(BOOST_PP_ENUM_PARAMS(n, s))>::type type;  \
  };                                                                        \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)

  #undef M0
  #undef M1
} }


#endif

