//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_TRIW_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_TRIW_HPP_INCLUDED
#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_triw triw
 *
 * \par Description
 * triw   upper triangular matrix discussed by wilkinson and others.
 *   triw(n,alpha,k) is the upper triangular matrix with
 *   ones on the diagonal and alphas on the first k >= 0 superdiagonals.
 *   n may be a 2-vector, in which case the matrix is n(1)-by-n(2)
 *   and upper trapezoidal.
 *   the defaults are alpha = -1, and k = n - 1. this yields the full
 *   upper triangular matrix discussed by kahan, golub and wilkinson.
 *
 *   notes:
 *   ostrowski [3] shows that
 *     cond(triw(n,2)) = cot(pi/(4*n))^2,
 *   and for large abs(alpha),
 *     cond(triw(n,alpha)) is approx. abs(alpha)^n*sin(pi/(4*n-2)).
 *
 *   adding -2^(2-n) to the (n,1) element makes triw(n) singular,
 *   as does adding -2^(1-n) to all elements in the first column.

 *   references:
 *   [1] G. H. Golub and J. H. Wilkinson, Ill-conditioned eigensystems and
 *       the computation of the Jordan canonical form, SIAM Review,
 *       18(4), 1976, pp. 578-619.
 *   [2] W. Kahan, Numerical linear algebra, Canadian Math. Bulletin,
 *       9 (1966), pp. 757-801.
 *   [3] A. M. Ostrowski, On the spectrum of a one-parametric family of
 *       matrices, J. Reine Angew. Math., 193 (3/4), 1954, pp. 143-160.
 *   [4] J. H. Wilkinson, Singular-value decomposition---basic aspects,
 *       in D.A.H. Jacobs, ed., Numerical Software---Needs and Availability,
 *       Academic Press, London, 1978, pp. 109-135.
 *
 *   Nicholas J. Higham
 *
 * \code
 * #include <nt2/include/functions/triw.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// triw actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag triw_ of functor triw
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct triw_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::triw_, triw, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::triw_, triw, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::triw_, triw, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::triw_, triw, 4)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::triw_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::triw_,Domain,N,Expr>
        : meta::value_as<Expr,1>
  {};

} }

#endif
