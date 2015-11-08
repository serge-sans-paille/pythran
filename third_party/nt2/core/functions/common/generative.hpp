//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_GENERATIVE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_GENERATIVE_HPP_INCLUDED

#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/core/include/functions/as_size.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// of_size + target
  NT2_FUNCTOR_IMPLEMENTATION( nt2::ext::pure_constant_<Tag>, tag::cpu_
                            , (T)(A0)(Tag)
                            , (fusion_sequence_<A0>)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename boost::remove_const<A0>::type        size_type;
    typedef meta::constant_<Tag,typename T::type>         constant_t;
    typedef meta::as_<typename constant_t::base_type>     target_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < Tag, container::domain
                                , size_type
                                , constant_t
                                , target_t
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const
    {
      return  boost::proto
            ::make_expr<Tag, container::domain>(a0, constant_t(), target_t());
    }
  };

  /// INTERNAL ONLY
  /// of_size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::ext::pure_constant_<Tag>, tag::cpu_
                            , (A0)(Tag)
                            , (fusion_sequence_<A0>)
                            )
  {
    typedef typename boost::remove_const<A0>::type          size_type;
    typedef meta::constant_<Tag,typename Tag::default_type> constant_t;
    typedef meta::as_<typename constant_t::base_type>       target_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < Tag, container::domain
                                , size_type
                                , constant_t
                                , target_t
                                >::type                   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return  boost::proto
            ::make_expr<Tag, container::domain> ( a0
                                                , constant_t()
                                                , target_t()
                                                );
    }
  };

  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::ext::pure_constant_<Tag>, tag::cpu_          \
                            , (Tag)BOOST_PP_REPEAT(n,M2,~)                      \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                            )                                                   \
  {                                                                             \
    typedef typename make_functor<Tag,A0>::type call_t;                         \
    BOOST_DISPATCH_RETURNS( n                                                   \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a) )      \
                          , (call_t()(nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a)))  \
                            )                                                   \
                          )                                                     \
  };                                                                            \
                                                                                \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::ext::pure_constant_<Tag>, tag::cpu_          \
                            , (Tag)BOOST_PP_REPEAT(n,M2,~)(T)                   \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                              (target_< scalar_< unspecified_<T> > >)           \
                            )                                                   \
  {                                                                             \
    typedef typename make_functor<Tag,A0>::type call_t;                         \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            , T const& tgt                                      \
                            )                                                   \
                          , (call_t() ( nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a)) \
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

  /// INTERNAL ONLY
  /// size(...)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::ext::pure_constant_<Tag>, tag::cpu_
                            , (A0)(Tag)
                            , ((ast_< A0, nt2::container::domain >))
                            )
  {
    typedef typename make_functor<Tag,A0>::type call_t;
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0)
                          , (call_t()(nt2::as_size(a0)))
                          )
  };

  /// INTERNAL ONLY
  /// size(...) + target
  NT2_FUNCTOR_IMPLEMENTATION( nt2::ext::pure_constant_<Tag>, tag::cpu_
                            , (Tag)(A0)(T)
                            , ((ast_< A0, nt2::container::domain >))
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename make_functor<Tag,A0>::type call_t;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, T const& tgt)
                          , (call_t()(nt2::as_size(a0),tgt))
                          )
  };
} }

#endif
