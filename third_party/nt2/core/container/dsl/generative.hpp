//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GENERATIVE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GENERATIVE_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  // This is the factorized value_type for all generative function.
  // For any given generative function tag GEN, the specialization of their
  // value_type is :
  //
  // namespace nt2 { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct value_type<GEN,Domain,N,Expr> : meta::generative_value<Expr>
  //  {};
  // } }
  //
  //============================================================================
  template<class Expr> struct generative_value
  {
    typedef typename boost::proto::result_of::child_c<Expr&,2>::type        c_t;
    typedef typename boost::proto::result_of::value<c_t>::value_type::type  type;
  };

  //============================================================================
  // This is the factorized size_of for all generative function.
  // For any given generative function tag GEN, the specialization of their
  // size_of is simply :
  //
  // namespace nt2 { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct size_of<GEN,Domain,N,Expr> : meta::generative_size<Expr>
  //  {};
  // } }
  //
  //============================================================================
  template<class Expr> struct generative_size : meta::boxed_size<Expr,0> {};
} }

#endif
