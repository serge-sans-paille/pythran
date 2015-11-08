//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_PLANEROT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_PLANEROT_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct planerot_ :  ext::tieable_<planerot_>
    {
      typedef ext::tieable_<planerot_>  parent;
    };
  }

  /**
   * @brief Perform Planerot computation
   *
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::planerot_, planerot, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::planerot_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::planerot_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
