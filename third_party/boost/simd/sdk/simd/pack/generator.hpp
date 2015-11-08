//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/dsl/typed_expression.hpp>
#include <boost/simd/dsl/functions/evaluate.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    struct mpl_2
    {
      template<class X, class Y>
      struct apply
      {
        typedef Y type;
      };
    };
  }

  struct generator
    : proto::transform<generator>
  {
    // normal case: return an expression
    template< class Expr, class State, class Data
            , class RawExpr = typename dispatch::meta::strip<Expr>::type
            , class Semantic = typename mpl::apply1< meta::typed_expression<details::mpl_2>, RawExpr>::type
            , class Enable = void
            >
    struct impl
         : proto::transform_impl<Expr, State, Data>
    {
      typedef expression<RawExpr, Semantic> result_type;

      BOOST_FORCEINLINE result_type
      operator()( typename impl::expr_param e
                , typename impl::state_param
                , typename impl::data_param
                ) const
      {
        result_type const that = {e};
        return that;
      }
    };

    // scalar or void case: evaluate the expression and return it
    template< class Expr, class State, class Data
            , class RawExpr, class Semantic
            >
    struct impl<Expr, State, Data, RawExpr, Semantic, typename enable_if< dispatch::meta::is_scalar<Semantic> >::type>
         : proto::transform_impl<Expr, State, Data>
    {
      typedef Semantic result_type;
      typedef expression<RawExpr, Semantic> simd_expr;

      BOOST_FORCEINLINE result_type
      operator()( typename impl::expr_param e
                , typename impl::state_param
                , typename impl::data_param
                ) const
      {
        simd_expr const that = {e};
        return evaluate(that);
      }
    };
  };
} }

#endif
