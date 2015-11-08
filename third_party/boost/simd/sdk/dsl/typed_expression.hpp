//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_DSL_TYPED_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_TYPED_EXPRESSION_HPP_INCLUDED

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/proto/traits.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class Lambda>
  struct typed_expression
  {
    template<class Expr, int N>
    struct apply_impl;

    template<class Expr>
    struct apply
      : apply_impl<Expr, proto::arity_of<Expr>::value>
    {
    };

    #define M0(z, n, t)                                                        \
    template<class Expr>                                                       \
    struct apply_impl<Expr, n>                                                 \
     : mpl::apply2< Lambda                                                     \
                  , Expr                                                       \
                  , typename dispatch::meta::                                  \
                    call< typename proto::                                     \
                          tag_of<Expr>::type                                   \
                          (                                                    \
                            BOOST_PP_ENUM(n, M1, ~)                            \
                          )                                                    \
                        >::type                                                \
                  >                                                            \
    {                                                                          \
    };                                                                         \
    /**/

    #define M1(z, n, t)                                                        \
    typename dispatch::meta::                                                  \
    as_ref< typename dispatch::meta::                                          \
            semantic_of< typename proto::result_of::                           \
                         child_c<Expr, n>::type                                \
                       >::type                                                 \
          >::type                                                              \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)

    #undef M1
    #undef M0

    // terminal case
    template<class Expr>
    struct apply_impl<Expr, 0>
     : mpl::apply2< Lambda
                  , Expr
                  , typename dispatch::meta::
                    call< typename proto::
                          tag_of<Expr>::type(Expr&)
                        >::type
                  >
    {
    };
  };
} } }

#endif
