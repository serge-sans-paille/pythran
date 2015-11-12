//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RANDI_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RANDI_HPP_INCLUDED

#include <nt2/core/functions/randi.hpp>
#include <nt2/core/include/functions/first_index.hpp>
#include <nt2/core/include/functions/as_size.hpp>
#include <nt2/core/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  // imax + size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              ((ast_< A1, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, A1 const& sz)
                          , (nt2::randi(a0,nt2::as_size(sz)))
                          )
  };

  // imin/max + size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              ((ast_< A1, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& sz)
                            , (nt2::randi(a0,nt2::as_size(sz)))
                          )
  };

  // imin/max + size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_< A0, nt2::container::domain >))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::randi_, container::domain
                                , typename A0::value_type
                                , typename A0::value_type
                                , typename boost::remove_const<A1>::type
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& sz) const
    {
      BOOST_ASSERT_MSG( numel(a0) <= 2, "randi: invalid range size");

      std::size_t i = first_index<1>(a0);

      typename A0::value_type imin = numel(a0) == 2 ? a0(i) : 1;
      typename A0::value_type imax = numel(a0) == 2 ? a0(i+1) : a0(i);

      return  boost::proto
            ::make_expr < nt2::tag::randi_
                        , container::domain
                        >( imin,imax, sz );
    }
  };

  // imin/max + size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_< A0, nt2::container::domain >))
                              ((ast_< A1, nt2::container::domain >))
                            )
  {
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::randi_, container::domain
                                , typename A0::value_type
                                , typename A0::value_type
                                , of_size_max
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& sz) const
    {
      BOOST_ASSERT_MSG( numel(a0) <= 2, "randi: invalid range size");

      std::size_t i = first_index<1>(a0);

      typename A0::value_type imin = numel(a0) == 2 ? a0(i) : 1;
      typename A0::value_type imax = numel(a0) == 2 ? a0(i+1) : a0(i);

      return  boost::proto
            ::make_expr < nt2::tag::randi_
                        , container::domain
                        >( imin,imax, nt2::as_size(sz) );
    }
  };

  // imin/max
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_
                            , (A0)
                            , ((ast_< A0, nt2::container::domain >))
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG( numel(a0) <= 2, "randi: invalid range size");

      std::size_t i = first_index<1>(a0);

      result_type imin = numel(a0) == 2 ? a0(i) : 1;
      result_type imax = numel(a0) == 2 ? a0(i+1) : a0(i);

      result_type that;
      current_prng_.generator_->randi(&that,0,1,imin,imax);
      return that;
    }
  };


  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randi_, tag::cpu_                       \
                            , (T)BOOST_PP_REPEAT(n,M2,~)                        \
                            , ((ast_<T, nt2::container::domain >))              \
                              BOOST_PP_REPEAT(n,M1,~)                           \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( T const& imax                                     \
                            , BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            )                                                   \
                          , (nt2::randi( imax                                   \
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
