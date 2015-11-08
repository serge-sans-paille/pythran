//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_COLS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_COLS_HPP_INCLUDED

#include <nt2/core/functions/cols.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/details/cols.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                             \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cols_, tag::cpu_                        \
                            , BOOST_PP_REPEAT(n,M2,~)(T)                        \
                            , BOOST_PP_REPEAT(n,M1,~)                           \
                              (scalar_< unspecified_<T> >)                      \
                            )                                                   \
  {                                                                             \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                     \
                          , ( BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a)        \
                            , T const& s                                        \
                            )                                                   \
                          , (nt2::cols( nt2::as_size(BOOST_PP_ENUM_PARAMS(n,a)) \
                                      , s                                       \
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
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cols_, tag::cpu_
                            , (T)
                            , (scalar_< unspecified_<T> >)
                            )
  {
    typedef T result_type;

    BOOST_FORCEINLINE result_type operator()(T const& s) const
    {
      return s;
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cols_, tag::cpu_
                            , (A0)(T)
                            , (fusion_sequence_<A0>)
                              (scalar_< unspecified_<T> >)
                            )
  {
    typedef typename boost::remove_const<A0>::type          size_type;
    typedef meta::constant_<nt2::tag::cols_,T>              constant_t;
    typedef meta::as_<typename constant_t::base_type>     target_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::cols_
                                , container::domain
                                , size_type
                                , constant_t
                                , target_t
                                >::type                     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& s) const
    {
      return  boost::proto
            ::make_expr < nt2::tag::cols_
                        , container::domain
                        > ( a0
                          , constant_t(s)
                          , target_t()
                          );
    }
  };
} }

#endif
