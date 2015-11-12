//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_KIND_ELEMENTWISE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_KIND_ELEMENTWISE_HPP_INCLUDED

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/proto/detail/deduce_domain.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace simd { namespace tag
{
  struct terminal_;
} } }

namespace nt2 { namespace ext
{
  //============================================================================
  // default kind_of for 0-2 arity
  //============================================================================
  template<typename Domain, typename Expr>
  struct kind_of<boost::simd::tag::terminal_, Domain, 0, Expr>
  {
    typedef typename Expr::kind_type  type;
  };

  template<typename Tag, typename Domain, typename Expr>
  struct kind_of<Tag, Domain, 1, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  A0;
    typedef typename A0::kind_type                                        type;
  };

  template<typename Tag, typename Domain, typename Expr>
  struct kind_of<Tag, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type A0;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type A1;
    typedef typename A0::kind_type                                      base0;
    typedef typename A1::kind_type                                      base1;

    typedef typename boost::proto::detail
                                 ::common_domain2<base0,base1>::type    type;
  };

  //============================================================================
  // default kind_of, sort semantic by order of closeness to their
  // common parent.
  //============================================================================
  #define M1(z,n,t)                                                            \
  typedef typename boost::proto::result_of::child_c<Expr&,n>::value_type A##n; \
  typedef typename A##n::kind_type                                       b##n; \
  /**/

  #define M0(z,n,t)                                                            \
  template<typename Tag, typename Domain, typename Expr>                       \
  struct kind_of<Tag, Domain, n, Expr>                                         \
  {                                                                            \
    BOOST_PP_REPEAT(n, M1, ~)                                                  \
    typedef typename boost::proto::detail::                                    \
                     common_domain##n<BOOST_PP_ENUM_PARAMS(n,b)>::type type;   \
  };                                                                           \
  /**/

  BOOST_PP_REPEAT_FROM_TO(3, BOOST_DISPATCH_MAX_ARITY, M0, ~)

  #undef M0
  #undef M1
} }


#endif

