//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_REDHEFF_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_REDHEFF_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_redheff redheff
 *
 *    a = gallery('redheff',n) is an n-by-n matrix of 0s and 1s
 *    defined by
 *       a(i,j) = 1, if j = 1 or if i divides j,
 *              = 0 otherwise.
 *
 *    properties:
 *    a has n-floor(log2(n))-1 eigenvalues equal to 1,
 *    a real eigenvalue (the spectral radius) approximately sqrt(n),
 *    a negative eigenvalue approximately -sqrt(n),
 *    and the remaining eigenvalues are provably "small".
 *
 *    the riemann hypothesis is true if and only if
 *    det(a) = o( n^(1/2+epsilon) ) for every epsilon > 0.
 *
 *    note:
 *    Barrett and Jarvis [1] conjecture that "the small eigenvalues
 *    all lie inside the unit circle abs(z) = 1". a proof of this
 *    conjecture, together with a proof that some eigenvalue tends to
 *    zero as n tends to infinity, would yield a new proof of the
 *    prime number theorem.
 *
 *   Reference:
 *    [1] W. W. Barrett and T. J. Jarvis, Spectral Properties of a
 *        Matrix of Redheffer, Linear Algebra and Appl.,
 *        162 (1992), pp. 673-683.
 *
 !* \par Header file
 *
 * \code
 * #include <nt2/include/functions/redheff.hpp>
 * \endcode
 *
 **/
//==============================================================================
// redheff actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag redheff_ of functor redheff
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct redheff_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::redheff_, redheff, 2)

}

#endif

