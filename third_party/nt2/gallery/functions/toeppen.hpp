//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_TOEPPEN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_TOEPPEN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_toeppen toeppen
 *
 *    p = toeppen(n,a,b,c,d,e) takes integer n and
 *    scalar a,b,c,d,e. p is the n-by-n sparse pentadiagonal toeplitz
 *    matrix with the diagonals: p(3,1)=a, p(2,1)=b, p(1,1)=c, p(1,2)=d,
 *    p(1,3)=e.
 *
 *    default: (a,b,c,d,e) = (1,-10,0,10,1) (a matrix of rutishauser).
 *    this matrix has eigenvalues lying approximately on the line segment
 *    2*cos(2*t) + 20*i*sin(t).
 *
 *    the pseudospectra of the following matrices are interesting:
 *    toeppen(32,0,1,0,0,1/4)  - `triangle'
 *    toeppen(32,0,1/2,0,0,1)  - `propeller'
 *    toeppen(32,0,1/2,1,1,1)  - `fish'
 *
 *    References:
 *    [1] R. M. Beam and R. F. Warming, The asymptotic spectra of banded
 *    Toeplitz and quasi-Toeplitz matrices, SIAM J. Sci. Comput. 14 (4),
 *    1993, pp. 971-1006.
 *    [2] H. Rutishauser, On test matrices, Programmation en Mathematiques
 *    Numeriques, Editions Centre Nat. Recherche Sci., Paris, 165, 1966,
 *    pp. 349-365.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/toeppen.hpp>
 * \endcode
 *
 **/
//==============================================================================
// toeppen actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag toeppen_ of functor toeppen
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct toeppen_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toeppen_, toeppen, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toeppen_, toeppen, 6)

}

#endif

