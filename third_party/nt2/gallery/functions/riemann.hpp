//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RIEMANN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RIEMANN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_riemann riemann
 *
 * matrix associated with the riemann hypothesis.
 *    a =riemann(n) is an n-by-n matrix for which the
 *    riemann hypothesis is true if and only if
 *       det(a) = o( n! n^(-1/2+epsilon) ), for every epsilon > 0.
 *
 *    a = b(2:n+1, 2:n+1), where
 *       b(i,j) = i-1 if i divides j, and -1 otherwise.
 *
 *    properties include, with m = n+1:
 *       each eigenvalue e(i) satisfies abs(e(i)) <= m - 1/m.
 *       i <= e(i) <= i+1 with at most m-sqrt(m) exceptions.
 *       all integers in the interval (m/3, m/2] are eigenvalues.
 *
 *
 *    Reference:
 *    F. Roesler, Riemann's hypothesis as an eigenvalue problem,
 *    Linear Algebra and Appl., 81 (1986), pp. 153-198.
 *
 *    Nicholas J. Higham
 *    Copyright 1984-2005 The MathWorks, Inc.
 *    $Revision: 1.10.4.1 $  $Date: 2005/11/18 14:15:30 $
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/riemann.hpp>
 * \endcode
 *
 **/
//==============================================================================
// riemann actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag riemann_ of functor riemann
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct riemann_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::riemann_, riemann, 2)

}

#endif

