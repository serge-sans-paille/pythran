//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_EXPRESSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_EXPRESSION_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/meta/settings_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Semantic of NT2 expression lies in its ResultType template parameter
  //============================================================================
  template<class Expr, class ResultType>
  struct semantic_of< nt2::container::expression<Expr, ResultType> >
  {
    typedef ResultType type;
  };

  template<typename Expr, typename ResultType>
  struct terminal_of< nt2::container::expression<Expr, ResultType> >
  {
    typedef typename terminal_of<ResultType>::type type;
  };
} } }

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY : Option of expression use its settings and semantic
  template<typename Expr, typename Result, typename Tag>
  struct  option<nt2::container::expression<Expr, Result>, Tag>
        : option<Result, Tag>
  {};

  /// INTERNAL ONLY : Extract settings from expression
  template<typename Expr, typename Result>
  struct settings_of< nt2::container::expression<Expr, Result> >
  {
    typedef typename meta::settings_of<Result>::type  type;
  };
} }

#endif
