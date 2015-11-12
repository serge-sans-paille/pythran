//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_INDEX_VALUE_TYPE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_INDEX_VALUE_TYPE_HPP_INCLUDED

#include <nt2/core/functions/function_index.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Extension of value_type to handle function_index call nodes
  // The returned value is the value_type of the leftmost children of the node
  //============================================================================
  template<class Expr, class Domain, int N>
  struct value_type<tag::function_index_, Domain, N, Expr>
  {
    typedef std::size_t type;
  };
} }

#endif
