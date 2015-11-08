//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_HOMOT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_HOMOT_HPP_INCLUDED

#include <nt2/core/functions/homot.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/core/functions/details/homot.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::homot_, tag::cpu_
                            , (A0)(Seq)
                            , (scalar_<unspecified_<A0> >)
                              (fusion_sequence_<Seq>)
                            )
  {
    typedef typename boost::remove_const<Seq>::type     size_type;
    typedef meta::constant_<nt2::tag::homot_,A0>       constant_t;
    typedef meta::as_<typename constant_t::base_type> target_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::homot_
                                , container::domain
                                , size_type
                                , constant_t
                                , target_t
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Seq const& s) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::homot_
                        , container::domain
                        > ( s, constant_t(a0), target_t() );
    }
  };

  //============================================================================
  // Generates homot from scalar + N size value
  //============================================================================
  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::homot_, tag::cpu_                      \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(n),M2,~)             \
                            , (scalar_<unspecified_<A0> > )                     \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M1,~)   \
                            )                                                   \
  {                                                                             \
   BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                      \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_PP_INC(n)     \
                                                          , const A,& a         \
                                                          )                     \
                            )                                                   \
                          , (nt2::homot                                        \
                            ( a0, nt2::as_size                                  \
                              (BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n),a)) \
                            )                                                   \
                            )                                                   \
                          )                                                     \
  };                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M2
  #undef M1
  #undef M0
} }

#endif
