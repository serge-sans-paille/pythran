//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_FRANK_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_FRANK_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_frank frank
 *
 * \par Description
 *    f = frank(n, k) is the frank matrix of order n.  it is
 *    upper hessenberg with determinant 1. if k = 1, the elements are
 *    reflected about the anti-diagonal (1,n)--(n,1).  the eigenvalues
 *    of f may be obtained in terms of the zeros of the hermite
 *    polynomials.  they are positive and occur in reciprocal pairs;
 *    thus if n is odd, 1 is an eigenvalue.  f has floor(n/2)
 *    ill-conditioned eigenvalues---the smaller ones.
 *
 *    for large n, det(gallery('frank',n)) comes out far from 1.
 *    See [1] and [4] for discussions.
 *
 *    References:
 *    [1] W. L. Frank, Computing eigenvalues of complex matrices by
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
 *    [7] J. M. Varah, A generalization of the Frank matrix,
 *        SIAM J. Sci. Stat. Comput., 7 (1986), pp. 835-839.
 *
 *    References [3], [6], and [7] give details of the eigensystem.
 *
 * \code
 * #include <nt2/include/functions/frank.hpp>
 * \endcode
 *
**/
//==============================================================================
// frank actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag frank_ of functor frank
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct frank0_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
    struct frank1_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::frank0_, frank0, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::frank1_, frank1, 2)

  template < class T, class A0>
  typename meta::call<tag::frank0_(A0 const&, meta::as_<T>)>::type
  frank0(A0 const & n)
  {
    return frank0(n, meta::as_<T>());
  }
  template < class T, class A0>
  typename meta::call<tag::frank1_(A0 const&, meta::as_<T>)>::type
  frank1(A0 const & n)
  {
    return frank1(n, meta::as_<T>());
  }
}

#endif
