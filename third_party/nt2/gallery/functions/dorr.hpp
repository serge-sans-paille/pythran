//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_DORR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_DORR_HPP_INCLUDED
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_dorr dorr
 *
 * \par Description
 *  tie(c,d,e) = dorr(n,theta) returns the vectors defining a row
 *  diagonally dominant, tridiagonal n-by-n matrix that is ill-conditioned
 *  for small values of theta >= 0. theta defaults to 0.01.
 *
 *  a = dorr(n,theta) returns the (sparse) dorr matrix itself.
 *  this is the same as
 *      tie(c,d,e) = dorr(n,theta);
 *      a = tridiag(c,d,e);
 *
 *  the columns of inv(c) vary greatly in norm.
 *  the amount of diagonal dominance, ignoring rounding errors, is:
 *       mtimes(compar(c), ones(n,1)) = theta*(n+1)^2 * cons(of_size(n, 1), 1 0 0 ... 0 1).

 *  reference:
 *  f. w. dorr, an example of ill-conditioning in the numerical
 *  solution of singular perturbation problems, math. comp.,
 *  25 (1971), pp. 271-283.
 *
 *  Nicholas J. Higham
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/dorr.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// dorr actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag dorr_ of functor dorr
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct dorr_ : ext::tieable_<dorr_>
    {
      typedef ext::tieable_<dorr_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::dorr_, dorr, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::dorr_, dorr, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::dorr_, dorr, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::dorr_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::dorr_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};

} }

#endif
