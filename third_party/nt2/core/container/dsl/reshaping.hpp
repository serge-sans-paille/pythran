//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_RESHAPING_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_RESHAPING_HPP_INCLUDED

#include <nt2/sdk/meta/value_as.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  // This is the factorized size_of for all reshaping function.
  // For any given reshaping function tag RSH, the registration of their
  // size_of is simply :
  //
  // namespace nt2 { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct size_of<RSH,Domain,N,Expr> : meta::reshaping_size_of<Expr>
  //  {};
  // } }
  //
  //============================================================================
  template<class Expr>
  struct  reshaping_value
        : meta::value_as<Expr,1>
  {};
} }

#endif
