//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_RANDI_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_RANDI_HPP_INCLUDED

#include <nt2/core/functions/randi.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <nt2/core/include/functions/as_size.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace ext
{
  // randi(imax)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      result_type that;
      current_prng_.generator_->randi(&that,0,1,A0(1),a0);
      return that;
    }
  };

  // randi([imin imax])
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (S)
                            , (fusion_sequence_<S>)
                            )
  {
    typedef typename boost::fusion::result_of::value_at_c<S,0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(S const& minmax) const
    {
      result_type that;
      current_prng_.generator_->randi ( &that , 0,  1
                                , boost::fusion::at_c<0>(minmax)
                                , boost::fusion::at_c<1>(minmax)
                                );
      return that;
    }
  };

  // randi(imax, of_size)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)(S)
                            , (scalar_< integer_<A0> >)
                              (fusion_sequence_<S>)
                            )
  {
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::randi_, container::domain
                                , A0
                                , A0
                                , typename boost::remove_const<S>::type
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, S const& size) const
    {
      return  boost::proto
            ::make_expr<nt2::tag::randi_,container::domain>(A0(1),a0,size);
    }
  };

  // randi([imin imax], of_size)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)(S)
                            , (fusion_sequence_<A0>)
                              (fusion_sequence_<S>)
                            )
  {
    typedef typename boost::fusion::result_of::value_at_c<A0,0>::type v_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::randi_, container::domain
                                , v_t
                                , v_t
                                , typename boost::remove_const<S>::type
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, S const& size) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::randi_
                        , container::domain
                        > ( boost::fusion::at_c<0>(a0)
                          , boost::fusion::at_c<1>(a0)
                          , size
                          );
    }
  };

  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_                       \
                            , (T)BOOST_PP_REPEAT(n,M2,~)                        \
                            , (scalar_< integer_<T> >)                          \
                              BOOST_PP_REPEAT(n,M1,~)                           \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( T imax                                            \
                            , BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            )                                                   \
                          , (nt2::randi( imax                                   \
                                       , nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a))\
                                       )                                        \
                            )                                                   \
                          )                                                     \
  };                                                                            \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_                       \
                            , (S)BOOST_PP_REPEAT(n,M2,~)                        \
                            , (fusion_sequence_<S>)                             \
                              BOOST_PP_REPEAT(n,M1,~)                           \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( S const& rg                                       \
                            , BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            )                                                   \
                          , (nt2::randi( rg                                     \
                                       , nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a))\
                                       )                                        \
                            )                                                   \
                          )                                                     \
  };                                                                            \
  /**/


  // randi(imax, ... ) + randi([imin imax], ...)
  BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)

  #undef M0
  #undef M1
  #undef M2

} }

#endif
