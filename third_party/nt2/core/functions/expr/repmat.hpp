//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_REPMAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_REPMAT_HPP_INCLUDED

#include <nt2/core/functions/repmat.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates from an expression and an extent
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::remove_const<A1>::type     size_type;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::repmat_
                                , container::domain
                                , size_type
                                , A0 const&
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& s) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::repmat_
                        , container::domain
                        > ( s
                          , boost::cref(a0)
                          );
    }
  };

  //============================================================================
  // Generates from an expression and a size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
   BOOST_DISPATCH_RETURNS( 2, ( const A0& a0, const A1& a1)
                          , (nt2::repmat( a0, nt2::as_size(a1)))
                         )
  };

  //============================================================================
  // Generates repnum from scalar + N size value
  //============================================================================
  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_                      \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(n),M2,~)             \
                            , ((ast_<A0, nt2::container::domain>))              \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M1,~)   \
                            )                                                   \
  {                                                                             \
   BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                      \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_PP_INC(n)     \
                                                          , const A,& a         \
                                                          )                     \
                            )                                                   \
                          , (nt2::repmat                                        \
                            ( a0, nt2::as_size                                  \
                              (BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n),a)) \
                            )                                                   \
                            )                                                   \
                          )                                                     \
  };                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_PP_INC(NT2_MAX_DIMENSIONS)),M0,~)

  #undef M2
  #undef M1
  #undef M0
} }

#endif
