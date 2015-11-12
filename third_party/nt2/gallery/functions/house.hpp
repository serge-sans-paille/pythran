//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_HOUSE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_HOUSE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup algebra
 * \defgroup algebra_house house
 *
 * \par Description
 *    tie(v, beta, s) = house(x, k) takes an n-by-1 vector x
 *    and returns v and beta such that h*x = s*e_1,
 *    where e_1 is the first column of eye(n), abs(s) = norm(x),
 *    and h = eye(n) - beta*v*v' is a householder matrix.
 *    the parameter k determines the sign of s:
 *       k = 0 (default): sign(s) = -sign(x(1)) ("usual" choice),
 *       k = 1:           sign(s) = sign(x(1))  (alternative choice).
 *    if x is real then a further option, for real x only, is
 *       k = 2:           sign(s) = 1.
 *    if x is complex, then sign(x) = exp(i*arg(x)) which equals x./abs(x)
 *    when x ~= 0.
 *    in two special cases v = 0, beta = 1 and s = x(1) are returned
 *    (hence h = i, which is not strictly a householder matrix):
 *       - when x = 0.
 *       - when x = alpha*e_1 and either k = 1, or k = 2 and alpha >= 0.
 *
 *    References:
 *    [1] G. H. Golub and C. F. Van Loan, Matrix Computations, third edition,
 *        Johns Hopkins University Press, Baltimore, Maryland, 1996, Sec. 5.1.
 *    [2] N. J. Higham, Accuracy and Stability of Numerical Algorithms,
 *        Second edition, Society for Industrial and Applied Mathematics,
 *        Philadelphia, 2002, Sec. 19.1.
 *    [3] G. W. Stewart, Introduction to Matrix Computations, Academic Press,
 *        New York, 1973, pp. 231-234, 262.
 *    [4] J. H. Wilkinson, The Algebraic Eigenvalue Problem, Oxford University
 *        Press, 1965, pp. 48-50.
 *
 *    Nicholas J. Higham
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/house.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// house actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag house_ of functor house
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct house_ : ext::tieable_<house_>
    {
      typedef ext::tieable_<house_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::house_, house, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::house_, house, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::house_, house, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<tag::house_,Domain, 3, Expr>
        : meta::size_as<Expr, 2>
  {};

  template<class Domain, class Expr>
  struct  value_type<tag::house_, Domain, 3, Expr>
        : meta::value_as<Expr, 0>
  {};

} }

#endif
