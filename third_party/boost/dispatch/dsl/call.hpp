#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DSL_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// This file generate basic EDSL expression wrapper over any nt2 function
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/make_expr.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

#if defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/selection/min.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#endif

namespace boost { namespace dispatch { namespace tag
{
  /// INTERNAL ONLY
  struct ast_ {};
}
namespace meta
{
  template<class T>
  struct proto_tag
  {
    typedef T type;
  };

  template<class T>
  struct is_formal : is_formal<typename T::parent>
  {
  };

  template<>
  struct is_formal<tag::formal_>
   : mpl::true_
  {
  };

  template<class T>
  struct is_formal<unknown_<T> >
   : mpl::false_
  {
  };
} } }

////////////////////////////////////////////////////////////////////////////////
// Defines the catch-all call for proto expression
////////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/dsl/preprocessed/call.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call.hpp")
#undef BOOST_FORCEINLINE
#endif

#define M1(z,n,t) boost::dispatch::meta::as_child(BOOST_PP_CAT(a,n))
#define M2(z,n,t) (BOOST_PP_CAT(A,n))
#define M3(z,n,t) (unspecified_<BOOST_PP_CAT(A,n)>)
#define M4(z,n,t) boost::reference_wrapper<A##n>(a##n)

namespace boost { namespace dispatch { namespace meta
{
  #define BOOST_PP_ITERATION_PARAMS_1 (4, ( 1, BOOST_PP_MIN( BOOST_DISPATCH_MAX_ARITY              \
                                                           , BOOST_PROTO_MAX_ARITY                 \
                                                           )                                       \
                                          , "boost/dispatch/dsl/call.hpp"                          \
                                          , 1                                                      \
                                          )                                                        \
                                    )
  #include BOOST_PP_ITERATE()

  template<class Func,class Dummy>
  struct implement<Func(tag::ast_),tag::formal_,Dummy>
  {
    template<class Sig>
    struct result;

    #define BOOST_PP_ITERATION_PARAMS_1 (4, ( 1, BOOST_PP_MIN( BOOST_DISPATCH_MAX_ARITY            \
                                                             , BOOST_PROTO_MAX_ARITY               \
                                                             )                                     \
                                            , "boost/dispatch/dsl/call.hpp"                        \
                                            , 2                                                    \
                                            )                                                      \
                                      )
    #include BOOST_PP_ITERATE()
  };
} } }

#undef M1
#undef M2
#undef M3
#undef M4

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
#endif

#else
#define n BOOST_PP_ITERATION()
#if BOOST_PP_ITERATION_FLAGS() == 1
  BOOST_DISPATCH_REGISTER_TO_IF( (boost)(dispatch)(meta), unspecified_<Func>
                               , tag::formal_
                               , (Func)BOOST_PP_REPEAT(n,M2,~)
                               , (mpl::and_< mpl::not_< is_formal<Func> >
                                           , any < boost::proto::
                                                   is_expr<boost::mpl::_>
                                                 , BOOST_PP_ENUM_PARAMS(n,A)
                                                 >
                                           >
                                 )
                               , BOOST_PP_REPEAT(n,M3,~)
                               , (implement<Func(tag::ast_), tag::formal_>)
                               )
#else
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>
    {
      typedef typename boost::proto::result_of::
      make_expr < typename meta::proto_tag<Func>::type
                , BOOST_PP_ENUM_BINARY_PARAMS(n, typename meta::
                                       as_ref<A, >::type BOOST_PP_INTERCEPT)
                >::type type;
    };
    template<BOOST_PP_ENUM_PARAMS(n,class A)>
    BOOST_FORCEINLINE
    typename result<implement
                    (BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a))
                   >::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
      return boost::proto::
      make_expr< typename meta::proto_tag<Func>::type >
               ( BOOST_PP_ENUM(n, M4, ~) );
    }
#endif
#undef n
#endif
