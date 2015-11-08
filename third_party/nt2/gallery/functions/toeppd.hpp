//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_TOEPPD_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_TOEPPD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_toeppd toeppd
 *
 * toeppd symmetric positive definite toeplitz matrix.
 *    toeppd(n, w,theta) or  toeppd<T>(n, m)is an n-by-n symmetric positive
 *    semi-definite (spd) toeplitz matrix. it is composed of the sum of
 *    m rank 2 (or, for certain theta rank 1) spd toeplitz matrices.
 *    specifically,
 *       t = w(1)*t(theta(1)) + ... + w(m)*t(theta(m)),
 *    where t(theta(k)) has (i,j) element cos(2*pi*theta(k)*(i-j)).
 *
 *    defaults: m = n, w = rand(m,1), theta = rand(m,1).
 *
 *    Reference:
 *    G. Cybenko and C. F. Van Loan, Computing the minimum eigenvalue of
 *    a symmetric positive definite Toeplitz matrix, SIAM J. Sci. Stat.
 *    Comput., 7 (1986), pp. 123-131.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/toeppd.hpp>
 * \endcode
 *
 **/

namespace nt2 {
  namespace tag
  {
    /*!
     * \brief Define the tag toeppd_ of functor toeppd
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct toeppd_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toeppd_, toeppd, 3)

}

#endif

