//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CONDEX_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CONDEX_HPP_INCLUDED
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_condex condex
 *
 * \par Description
%CONDEX "Counter-examples" to matrix condition number estimators.
 *  condex(n,k,theta) is a "counter-example" matrix to a
 *  condition estimator. it has order n and scalar parameter
 *  theta (default 100). the matrix, its natural size, and the
 *  estimator to which it applies are specified by k as follows:
 *     k = 1:   4-by-4,     linpack.
 *     k = 2:   3-by-3,     linpack.
 *     k = 3:   arbitrary,  linpack (independent of theta)
 *     k = 4:   n >= 4,     lapack (rcond) (default).
 *                          it is the inverse of this matrix
 *                          that is a counter-example.
 *  if n is not equal to the natural size of the matrix, then
 *  the matrix is padded out with an identity matrix to order n.

 *  note: in practice, the k = 4 matrix is not usually a counter-example
 *  because of the rounding errors in forming it.
 *
 *  References:
 *  [1] A. K. Cline and R. K. Rew, A set of counter-examples to three
 *      condition number estimators, SIAM J. Sci. Stat. Comput.,
 *      4 (1983), pp. 602-611.
 *  [2] N. J. Higham, FORTRAN codes for estimating the one-norm of a
 *      real or complex matrix, with applications to condition
 *      estimation (Algorithm 674), ACM Trans. Math. Soft., 14 (1988),
 *      pp. 381-396.
 *  [3] N. J. Higham, Accuracy and Stability of Numerical Algorithms,
 *      Second edition, Society for Industrial and Applied Mathematics,
 *      Philadelphia, 2002, Chap. 15.
 *
 *  Nicholas J. Higham
 *
 * \code
 * #include <nt2/include/functions/condex.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// condex actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag condex_ of functor condex
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct condex_ : ext::unspecified_<condex_>
    {
      typedef ext::unspecified_<condex_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::condex_, condex, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::condex_, condex, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::condex_, condex, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::condex_, condex, 4)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::condex_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::condex_,Domain,N,Expr>
        : meta::value_as<Expr,2>
  {};

} }

#endif
