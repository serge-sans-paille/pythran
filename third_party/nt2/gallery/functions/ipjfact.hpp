//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_IPJFACT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_IPJFACT_HPP_INCLUDED
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_ipjfact ipjfact
 *
 * \par Description
 * ipjfact hankel matrix with factorial elements.
 *    tie(a,d) = ipjfact(n,k) returns a, an n-by-n
 *    hankel matrix and d, the determinant of a, which is
 *    known explicity.
 *
 *    if k = 0 (the default), then the elements of a are
 *       a(i,j) = (i+j)!
 *    if k = 1, then the elements of a are
 *       a(i,j) = 1/(i+j)!
 *
 *    note: the inverse of a is also known explicitly.
 *    acknowledgement: suggested by p. r. graves-morris.
 *
 *    reference:
 *    M. J. C. Gover, the explicit inverse of factorial hankel
 *    matrices, dept. of mathematics, university of bradford, 1993.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ipjfact.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// ipjfact actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag ipjfact_ of functor ipjfact
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct ipjfact_ : ext::tieable_<ipjfact_>
    {
      typedef ext::tieable_<ipjfact_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::ipjfact_, ipjfact, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::ipjfact_, ipjfact, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::ipjfact_, ipjfact, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::ipjfact_,Domain,N,Expr>
        : meta::boxed_size<Expr,3>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::ipjfact_,Domain,N,Expr>
        : meta::value_as<Expr,2>
  {};

} }

#endif
