//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INDICES_HPP_INCLUDED

#include <nt2/core/functions/indices.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 {  namespace ext
{
  /// INTERNAL ONLY
  /// Along only returns a scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)
                            , ((array_< scalar_< integer_<A0> >
                                      , boost::mpl::size_t<2>
                                      >
                              ))
                            )
  {
    typedef double result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& s) const
    {
      return static_cast<double>(s[1]);
    }
  };

  /// INTERNAL ONLY
  /// Along only returns a scalar wityh a given target type
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(T)
                            , ((array_< scalar_< integer_<A0> >
                                      , boost::mpl::size_t<2>
                                      >
                              ))
                              (target_< unspecified_<T> >)
                            )
  {
    typedef typename T::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& s, T const&) const
    {
      return static_cast<typename T::type>(s[1]);
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              ((array_< scalar_< integer_<A1> >
                                      , boost::mpl::size_t<2>
                                      >
                              ))
                            )
  {
    typedef typename boost::remove_const<A0>::type          size_type;
    typedef meta::constant_<nt2::tag::indices_,double>      constant_t;
    typedef meta::as_<constant_t::base_type>              target_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::indices_
                                , container::domain
                                , size_type
                                , constant_t
                                , target_t
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& s) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::indices_
                        , container::domain
                        > ( a0
                          , constant_t(s[0],s[1])
                          , target_t()
                          );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)(T)
                            , (fusion_sequence_<A0>)
                              ((array_< scalar_< integer_<A1> >
                                      , boost::mpl::size_t<2>
                                      >
                              ))
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename boost::remove_const<A0>::type                size_type;
    typedef meta::constant_<nt2::tag::indices_,typename T::type>  constant_t;
    typedef meta::as_<typename constant_t::base_type>           target_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::indices_
                                , container::domain
                                , size_type
                                , constant_t
                                , target_t
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& s, T const&) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::indices_
                        , container::domain
                        > ( a0
                          , constant_t(s[0],s[1])
                          , target_t()
                          );
    }
  };


  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_                     \
                            , BOOST_PP_REPEAT(n,M2,~)(X)                        \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                              ((array_< scalar_< integer_<X> >                  \
                                      , boost::mpl::size_t<2>                   \
                                      >                                         \
                              ))                                                \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            , X const& x                                        \
                            )                                                   \
                          , (nt2::indices                                       \
                                  ( nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a))     \
                                  , x                                           \
                                  )                                             \
                            )                                                   \
                          )                                                     \
  };                                                                            \
                                                                                \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_                     \
                            , BOOST_PP_REPEAT(n,M2,~)(X)(T)                     \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                              ((array_< scalar_< integer_<X> >                  \
                                      , boost::mpl::size_t<2>                   \
                                      >                                         \
                              ))                                                \
                              (target_< scalar_< unspecified_<T> > >)           \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_ADD(n,2)                                   \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            , X const& x, T const& tgt                          \
                            )                                                   \
                          , (nt2::indices                                       \
                                  ( nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a))     \
                                  , x, tgt                                      \
                                  )                                             \
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
