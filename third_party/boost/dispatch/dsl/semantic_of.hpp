//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DSL_SEMANTIC_OF_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_SEMANTIC_OF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

////////////////////////////////////////////////////////////////////////////////
// For a given Proto expression, retrieves its semantic information, i.e.
// the type that it represents.
// void by default, identity on non-expressions.
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace details
{
  template<class Expr, class Enable = void>
  struct semantic_of
  {
    typedef Expr type;
  };

  template<class Expr>
  struct semantic_of<Expr, typename Expr::proto_is_expr_>
  {
    typedef void type;
  };
}

namespace meta
{
  template<class Expr, class Enable = void>
  struct semantic_of
   : details::semantic_of<Expr>
  {
  };

  template<class Expr>
  struct semantic_of<const Expr, typename enable_if_c<Expr::proto_arity_c == 0>::type>
    : add_const<typename semantic_of<Expr>::type>
  {
  };

  template<class Expr>
  struct semantic_of<const Expr, typename disable_if_c<Expr::proto_arity_c == 0>::type>
    : semantic_of<Expr>
  {
  };

  template<class Expr>
  struct semantic_of<Expr&, typename enable_if_c<Expr::proto_arity_c == 0>::type>
    : add_reference<typename semantic_of<Expr>::type>
  {
  };

  template<class Expr>
  struct semantic_of<Expr&, typename disable_if_c<Expr::proto_arity_c == 0>::type>
    : semantic_of<Expr>
  {
  };

} } }

#endif
