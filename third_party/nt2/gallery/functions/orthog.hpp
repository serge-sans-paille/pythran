//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_ORTHOG_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_ORTHOG_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_orthog orthog
 *
 * orthog orthogonal and nearly orthogonal matrices.
 *    q = orthog<K, T>(n) selects the k'th type of matrix of
 *    order n. K > 0 for exactly orthogonal matrices, and K < 0 for
 *    diagonal scalings of orthogonal matrices.
 *
 *    available types are:
 *    k = 1:  q(i,j) = sqrt(2/(n+1)) * sin( i*j*pi/(n+1) )
 *            symmetric eigenvector matrix for second difference matrix.
 *            this is the default k.
 *    k = 2:  q(i,j) = 2/sqrt(2*n+1)) * sin( 2*i*j*pi/(2*n+1) )
 *            symmetric.
 *    k = 3:  q(r,s) = exp(2*pi*i*(r-1)*(s-1)/n) / sqrt(n)
 *            unitary, the fourier matrix.  q^4 is the identity.
 *            this is essentially the same matrix as fft(eye(n))/sqrt(n)!
 *    k = 4:  helmert matrix: a permutation of a lower hessenberg matrix,
 *            whose first row is ones(1:n)/sqrt(n).
 *    k = 5:  q(i,j) = sin( 2*pi*(i-1)*(j-1)/n ) + cos( 2*pi*(i-1)*(j-1)/n ).
 *            symmetric matrix arising in the hartley transform.
 *    k = 6:  q(i,j) = sqrt(2/n)*cos( (i-1/2)*(j-1/2)*pi/n ).
 *            symmetric matrix arising as a discrete cosine transform.
 *    k = 7:  a particular householder matrix: symmetric with
 *            column sums sum(q) = [sqrt(n) zeros(1,n-1)].
 *    k = -1: q(i,j) = cos( (i-1)*(j-1)*pi/(n-1) )
 *            chebyshev vandermonde-like matrix, based on extrema
 *            of t(n-1).
 *    k = -2: q(i,j) = cos( (i-1)*(j-1/2)*pi/n) )
 *            chebyshev vandermonde-like matrix, based on zeros of t(n).
 *
 *    References:
 *    [1] N. J. Higham and D. J. Higham, Large growth factors in Gaussian
 *        elimination with pivoting, SIAM J. Matrix Analysis and  Appl.,
 *        10 (1989), pp. 155-164.
 *    [2] P. Morton, On the eigenvectors of Schur's matrix, J. Number Theory,
 *        12 (1980), pp. 122-127. (Re. orthog(n, 3))
 *    [3] H. O. Lancaster, The Helmert Matrices, Amer. Math. Monthly,
 *        72 (1965), pp. 4-12.
 *    [4] D. Bini and P. Favati, On a matrix algebra related to the discrete
 *        Hartley transform, SIAM J. Matrix Anal. Appl., 14 (1993),
 *        pp. 500-507.
 *    [5] G. Strang, The discrete cosine transform, SIAM Review, 41 (1999),
 *        pp. 135-147.
 *    [6] R. N. Khoury, Closest matrices in the space of generalized doubly
 *        stochastic matrices, J. Math. Anal. and Appl., 222 (1998), pp. 562-568.
 *        (Re. orthog(n, 7))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/orthog.hpp>
 * \endcode
 *
 **/
//==============================================================================
// orthog actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag orthog_ of functor orthog
     *        in namespace nt2::tag for toolbox algebra
    **/

#define NT2_FORMAL(Name)                            \
    struct Name : boost::dispatch::tag::formal_     \
    {                                               \
      typedef boost::dispatch::tag::formal_ parent; \
    }                                               \
        /**/

    NT2_FORMAL(orthog1_);
    NT2_FORMAL(orthog2_);
    NT2_FORMAL(orthog3_);
    NT2_FORMAL(orthog4_);
    NT2_FORMAL(orthog5_);
    NT2_FORMAL(orthog6_);
    NT2_FORMAL(orthog7_);
    NT2_FORMAL(orthogm1_);
    NT2_FORMAL(orthogm2_);

#undef NT2_FORMAL
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog1_, orthog1, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog2_, orthog2, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog3_, orthog3, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog4_, orthog4, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog5_, orthog5, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog6_, orthog6, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthog7_, orthog7, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthogm1_, orthogm1, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::orthogm2_, orthogm2, 2)

}

#endif

