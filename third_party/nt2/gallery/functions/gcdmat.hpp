//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GCDMAT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GCDMAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_gcdmat gcdmat
 *
 * \par Description
 *    f = gcdmat(n, k) is the gcdmat matrix of order n.  it is
 *    upper hessenberg with determinant 1. if k = 1, the elements are
 *    reflected about the anti-diagonal (1,n)--(n,1).  the eigenvalues
 *    of f may be obtained in terms of the zeros of the hermite
 *    polynomials.  they are positive and occur in reciprocal pairs;
 *    thus if n is odd, 1 is an eigenvalue.  f has floor(n/2)
 *    ill-conditioned eigenvalues---the smaller ones.
 *
 *    for large n, det(gallery('gcdmat',n)) comes out far from 1.
 *    See [1] and [4] for discussions.
 *
 *    References:
 *    [1] W. L. Gcdmat, Computing eigenvalues of complex matrices by
 *        determinant evaluation and by methods of Danilewski and Wielandt,
 *        J. Soc. Indust. Appl. Math., 6 (1958), pp. 378-392 (see pp. 385
 *        and 388).
 *    [2] G. H. Golub and J. H. Wilkinson, Ill-conditioned eigensystems and
 *        the computation of the Jordan canonical form, SIAM Review,
 *        18 (1976), pp. 578-619 (Section 13).
 *    [3] H. Rutishauser, On test matrices, Programmation en Mathematiques
 *        Numeriques, Editions Centre Nat. Recherche Sci., Paris, 165,
 *        1966, pp. 349-365.  Section 9.
 *    [4] J. H. Wilkinson, Error analysis of floating-point computation,
 *        Numer. Math., 2 (1960), pp. 319-340 (Section 8).
 *    [5] J. H. Wilkinson, The Algebraic Eigenvalue Problem, Oxford
 *        University Press, 1965 (pp. 92-93).
 *    [6] P. J. Eberlein, A note on the matrices denoted by B_n,
 *        SIAM J. Appl. Math., 20 (1971), pp. 87-92.
 *    [7] J. M. Varah, A generalization of the Gcdmat matrix,
 *        SIAM J. Sci. Stat. Comput., 7 (1986), pp. 835-839.
 *
 *    References [3], [6], and [7] give details of the eigensystem.
 *
 * \code
 * #include <nt2/include/functions/gcdmat.hpp>
 * \endcode
 *
**/
//==============================================================================
// gcdmat actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag gcdmat_ of functor gcdmat
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct gcdmat_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::gcdmat_, gcdmat, 2)


  template < class T, class A0>
  typename meta::call<tag::gcdmat_(A0 const&, meta::as_<T>)>::type
  gcdmat(A0 const & n)
  {
    return gcdmat(n, meta::as_<T>());
  }

}

#endif
