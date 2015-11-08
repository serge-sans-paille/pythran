//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ARRAYFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ARRAYFUN_HPP_INCLUDED

#include <nt2/core/functions/arrayfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

namespace nt2 { namespace ext
{
  #define M0(z, n, t) (A##n)
  #define M1(z, n, t) (generic_< unspecified_<A##n> >)

  #define M3(z, n, t)                                                                              \
  typename boost::dispatch::meta::                                                                 \
  as_ref< typename meta::                                                                          \
          call< tag::run_( typename boost::proto::result_of::child_c<Expr&, n+1>::type             \
                         , State const&                                                            \
                         , typename boost::simd::ext::                                             \
                           adapt_data< typename boost::proto::result_of::child_c<Expr, n+1>::type  \
                                     , Data                                                        \
                                     >::type                                                       \
                         )                                                                         \
              >::type                                                                              \
        >::type                                                                                    \
  /**/

  #define M4(z, n, t) nt2::run(boost::proto::child_c<n+1>(expr), state, boost::simd::ext::adapt_data<typename boost::proto::result_of::child_c<Expr, n+1>::type, Data>::call(data))

  #define M2(z, n, t)                                                                              \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arrayfun_, tag::cpu_                                       \
                            , (F)BOOST_PP_REPEAT(n, M0, ~)                                         \
                            , (unspecified_<F>)                                                    \
                              BOOST_PP_REPEAT(n, M1, ~)                                            \
                            )                                                                      \
  {                                                                                                \
    typedef typename meta::result_of<F(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))>::type result_type; \
                                                                                                   \
    BOOST_FORCEINLINE result_type                                                                  \
    operator()(F const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const                      \
    {                                                                                              \
      return f(BOOST_PP_ENUM_PARAMS(n, a));                                                        \
    }                                                                                              \
  };                                                                                               \
                                                                                                   \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_                                            \
                            , (Expr)(State)(Data)                                                   \
                            , ((node_<Expr, nt2::tag::arrayfun_, boost::mpl::long_<n+1>, nt2::container::domain>)) \
                              (generic_< integer_<State> >)                                        \
                              (unspecified_<Data>)                                                 \
                            )                                                                      \
  {                                                                                                \
    typedef typename meta::                                                                        \
            result_of< typename boost::proto::result_of::value< typename boost::proto::result_of::child_c<Expr, 0>::type >::type \
                       ( BOOST_PP_ENUM(n, M3, ~) )                                                 \
                     >::type result_type;                                                          \
                                                                                                   \
    BOOST_FORCEINLINE result_type                                                                  \
    operator()(Expr& expr, State const& state, Data const& data) const                             \
    {                                                                                              \
      return boost::proto::value(boost::proto::child_c<0>(expr))(BOOST_PP_ENUM(n, M4, ~));         \
    }                                                                                              \
  };
  /**/

  BOOST_PP_REPEAT_FROM_TO(1, 4, M2, ~)
  #undef M4
  #undef M3
  #undef M2
  #undef M1
  #undef M0

} }

#endif
