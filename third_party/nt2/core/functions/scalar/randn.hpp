//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_RANDN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_RANDN_HPP_INCLUDED

#include <nt2/core/functions/randn.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <nt2/core/include/functions/as_size.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// target
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randn_, tag::cpu_
                            , (T)
                            , (target_< scalar_< floating_<T> > >)
                            )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(T const&) const
    {
      result_type that;
      current_prng_.generator_->randn(&that,0,1);
      return that;
    }
  };

  /// INTERNAL ONLY
  /// of_size + target
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randn_, tag::cpu_
                            , (T)(A0)
                            , (fusion_sequence_<A0>)
                              (target_< scalar_< floating_<T> > >)
                            )
  {
    typedef typename boost::remove_const<A0>::type            size_type;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::randn_, container::domain
                                , size_type
                                , T
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& tgt) const
    {
      return  boost::proto
            ::make_expr<nt2::tag::randn_,container::domain>( a0, tgt );
    }
  };

  /// INTERNAL ONLY
  /// of_size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randn_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    typedef typename boost::remove_const<A0>::type            size_type;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::randn_, container::domain
                                , size_type
                                , meta::as_<double>
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::randn_
                        , container::domain
                        >( a0, meta::as_<double>() );
    }
  };

  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randn_, tag::cpu_                        \
                            , BOOST_PP_REPEAT(n,M2,~)                           \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( n                                                   \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a) )      \
                          ,  nt2::randn(nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a))) \
                          )                                                     \
  };                                                                            \
                                                                                \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::randn_, tag::cpu_                        \
                            , BOOST_PP_REPEAT(n,M2,~)(T)                        \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                              (target_< scalar_< floating_<T> > >)              \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            , T const& tgt                                      \
                            )                                                   \
                          , (nt2::randn( nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a)) \
                                      , tgt                                     \
                                      )                                         \
                            )                                                   \
                          )                                                     \
  };                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)

  #undef M0
  #undef M1
  #undef M2

} }

#endif
