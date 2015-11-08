//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_VALUE_TYPE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_VALUE_TYPE_HPP_INCLUDED

namespace nt2 { namespace details
{
  //==========================================================================
  // Basic generator for the usual, non-overloaded case.
  //==========================================================================
  template<class Tag, class Domain, int N, class Expr> struct value_type;
} }

namespace nt2 { namespace ext
{
  //==========================================================================
  /*!
   * This extension point specify the type an expression actually models.
   * If most expressions model a reference to the equivalent container of their
   * domain, some may require to some other type with proper cref qualifier.
   * This meta-function enables a fine grain specification of this scheme.
   *
   * \tparam Tag    Top most tag of the expression
   * \tparam Domain Domain of the expression
   * \tparam Arity  Number of children of the expression
   * \tparam Expr   The expression itself
   *
   * \return the type modeled by the nt2::container::expression
   *
  **/
  //==========================================================================
  template<class Tag, class Domain, int N, class Expr>
  struct value_type : details::value_type<Tag, Domain, N, Expr> {};
} }

#include <nt2/core/container/dsl/details/value/elementwise.hpp>

#endif
