//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CAUCHY_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CAUCHY_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_cauchy cauchy
 *
 * \par Description
 *   c = cauchy(x,y), where x and y are n-vectors, is the
 *   n-by-n matrix with c(i,j) = 1/(x(i)+y(j)). by default, y = x.
 *   if x is a scalar, cauchy(x) is the same as
 *   cauchy(1:x).
 *
 *   explicit formulas are known for the elements of inv(c) and det(c).
 *   det(c) is nonzero if x and y both have distinct elements.
 *   c is totally positive if 0 < x(1) < ... < x(n) and
 *                            0 < y(1) < ... < y(n).

 *   references:
 *   [1] d. e. knuth, the art of computer programming, volume 1,
 *       fundamental algorithms, third edition, addison-wesley, reading,
 *       massachusetts, 1997.
 *   [2] e. e. tyrtyshnikov, cauchy-toeplitz matrices and some applications,
 *       linear algebra and appl., 149 (1991), pp. 1-18.
 *   [3] o. taussky and m. marcus, eigenvalues of finite matrices, in
 *       survey of numerical analysis, j. todd, ed., mcgraw-hill, new york,
 *       1962, pp. 279-313. (the totally positive property is on p. 295.)
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cauchy.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// cauchy actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag cauchy_ of functor cauchy
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct cauchy_ : tag::formal_ { typedef tag::formal_ parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::cauchy_, cauchy, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::cauchy_, cauchy, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::cauchy_, cauchy, 3)
}

#endif
