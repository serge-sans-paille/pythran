#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_RUN_HPP_INCLUDED

#include <boost/simd/dsl/functions/run.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/include/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/meta/identity.hpp>

#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/selection/min.hpp>

namespace boost { namespace simd { namespace ext
{
  /* Adapt Data with Expr whenever it is a target */
  template<class Expr, class Data>
  struct adapt_data
  {
    typedef Data const& type;
    BOOST_FORCEINLINE static type call(Data const& data)
    {
      return data;
    }
  };

  template<class Expr, class Data>
  struct adapt_data< Expr, boost::dispatch::meta::as_<Data> >
  {
    typedef boost::dispatch::meta::as_<typename Expr::value_type> type;
    BOOST_FORCEINLINE static type call(boost::dispatch::meta::as_<Data> const&)
    {
      return type();
    }
  };

  template<class Expr, class T, class X>
  struct adapt_data< Expr, boost::dispatch::meta::as_< boost::simd::native<T, X> > >
  {
    typedef boost::dispatch::meta::as_<
      typename boost::simd::meta::vector_of<
        typename Expr::value_type
      , boost::simd::meta::cardinal_of< boost::simd::native<T, X> >::value
      >::type
    > type;
    BOOST_FORCEINLINE static type call(boost::dispatch::meta::as_< boost::simd::native<T, X> > const&)
    {
      return type();
    }
  };

  //============================================================================
  // Run an expression without state nor data
  //============================================================================
  #define M0(z,n,t)                                                                                \
  typename dispatch::meta::as_ref<                                                                 \
    typename dispatch::meta::result_of<                                                            \
      typename dispatch::meta::dispatch_call<                                                      \
        tag::run_(typename boost::proto::result_of::child_c<Expr&, n>::type)                       \
      >::type                                                                                      \
      ( typename boost::proto::result_of::child_c<Expr&, n>::type )                                \
    >::type                                                                                        \
  >::type                                                                                          \
  /**/

  #define M1(z,n,t)                                                                                \
  boost::dispatch::id(                                                                             \
    typename dispatch::meta::dispatch_call<                                                        \
      tag::run_(typename boost::proto::result_of::child_c<Expr&, n>::type)                         \
    >::type()                                                                                      \
    ( boost::proto::child_c<n>(expr) )                                                             \
  )                                                                                                \
  /**/

  //============================================================================
  // Run an expression with a state and a data
  //============================================================================
  #define M0d(z,n,t)                                                                               \
  typename dispatch::meta::as_ref<                                                                 \
    typename dispatch::meta::result_of<                                                            \
      typename dispatch::meta::dispatch_call<                                                      \
        tag::run_( typename boost::proto::result_of::child_c<Expr&, n>::type                       \
                 , State const&                                                                    \
                 , typename adapt_data< typename boost::proto::result_of::                         \
                                        child_c<Expr&, n>::value_type                              \
                                      , Data                                                       \
                                      >::type                                                      \
                 )                                                                                 \
      >::type                                                                                      \
      ( typename boost::proto::result_of::child_c<Expr&, n>::type                                  \
      , State const&                                                                               \
      , typename adapt_data< typename boost::proto::result_of::                                    \
                             child_c<Expr&, n>::value_type                                         \
                           , Data                                                                  \
                           >::type                                                                 \
      )                                                                                            \
    >::type                                                                                        \
  >::type                                                                                          \
  /**/

  #define M1d(z,n,t)                                                                               \
  boost::dispatch::id(                                                                             \
    typename dispatch::meta::dispatch_call<                                                        \
      tag::run_( typename boost::proto::result_of::child_c<Expr&, n>::type                         \
               , State const&                                                                      \
               , typename adapt_data< typename boost::proto::result_of::                           \
                                      child_c<Expr&, n>::value_type                                \
                                    , Data                                                         \
                                    >::type                                                        \
              )                                                                                    \
    >::type()                                                                                      \
    ( boost::proto::child_c<n>(expr)                                                               \
    , state                                                                                        \
    , adapt_data<typename boost::proto::result_of::child_c<Expr&, n>::value_type, Data>::call(data)\
    )                                                                                              \
  )                                                                                                \
  /**/

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_PP_MIN( BOOST_DISPATCH_MAX_ARITY              \
                                                           , BOOST_PROTO_MAX_ARITY                 \
                                                           )                                       \
                                          , "boost/simd/dsl/functions/generic/run.hpp"             \
                                          )                                                        \
                                      )
  #include BOOST_PP_ITERATE()

  #undef M0
  #undef M1
  #undef M0d
  #undef M1d

  //============================================================================
  // Run an expression with a state and data - Terminal cases
  // When run on a terminal, we directly jump into the terminal functor
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(T)(D)
                                    , ((node_<A0, unspecified_<T>, mpl::long_<0>, D>))
                                    )
  {
    typedef typename dispatch::meta::result_of<
      typename dispatch::meta::dispatch_call<T(A0&)>::type
      (A0&)
    >::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
      return typename dispatch::meta::dispatch_call<T(A0&)>::type()(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (A0)(T)(D)(State)(Data)
                                    , ((node_<A0, unspecified_<T>, mpl::long_<0>, D>))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    typedef typename dispatch::meta::result_of<
      typename dispatch::meta::dispatch_call<T(A0&, State const&, Data const&)>::type
      (A0&, State const&, Data const&)
    >::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& state, Data const& data) const
    {
      return typename dispatch::meta::dispatch_call<T(A0&, State const&, Data const&)>::type()(a0, state, data);
    }
  };
} } }

#endif
#else /* BOOST_PP_IS_ITERATING */

#define n BOOST_PP_ITERATION()

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::formal_
                                    , (Expr)(T)(D)
                                    , ((node_<Expr, unspecified_<T>, boost::mpl::long_<n>, D>))
                                    )
  {
    typedef typename dispatch::meta::result_of<
      typename dispatch::meta::dispatch_call<
        T( BOOST_PP_ENUM(n, M0, ~) )
      >::type
      ( BOOST_PP_ENUM(n, M0, ~) )
    >::type result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& expr) const
    {
      return typename dispatch::meta::dispatch_call<
        T( BOOST_PP_ENUM(n, M0, ~) )
      >::type()
      ( BOOST_PP_ENUM(n, M1, ~) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::run_, tag::cpu_
                                    , (Expr)(T)(D)(State)(Data)
                                    , ((node_<Expr, unspecified_<T>, boost::mpl::long_<n>, D>))
                                      (unspecified_<State>)
                                      (unspecified_<Data>)
                                    )
  {
    typedef typename dispatch::meta::result_of<
      typename dispatch::meta::dispatch_call<
        T( BOOST_PP_ENUM(n, M0d, ~) )
      >::type
      ( BOOST_PP_ENUM(n, M0d, ~) )
    >::type result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& expr, State const& state, Data const& data) const
    {
      return typename dispatch::meta::dispatch_call<
        T( BOOST_PP_ENUM(n, M0d, ~) )
      >::type()
      ( BOOST_PP_ENUM(n, M1d, ~) );
    }
  };

#undef n

#endif
