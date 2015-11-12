//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_MINIJ_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_MINIJ_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/one.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_minij minij
 *
 * \par Description
 * matrix with a(i,j) = min(i,j).
 *
 *    properties:
 *    a has eigenvalues 0.25*sqr(sec((1:n)*pi/(2*n+1))).
 *    inv(a) is tridiagonal. it is minus the second difference matrix
 *      except its (n,n) element is 1.
 *    a.^r is symmetric positive semidefinite for all nonnegative r.
 *    2*a-ones(n) (givens' matrix) has tridiagonal inverse and
 *      eigenvalues 0.5*sec((2*(1:n)-1)*pi/(4*n)).^2.
 *    flipud(triw,n,1) is a square root of a.
 *
 *    references:
 *    [1] R. Bhatia, Infinitely divisible matrices, Amer. Math. Monthly,
 *        (2005), to appear. (For the "A.^r" property.)
 *    [2] J. Fortiana and C. M. Cuadras, A family of matrices, the
 *        discretized Brownian bridge, and distance-based regression,
 *        Linear Algebra Appl., 264 (1997), pp. 173-188.  (For the
 *        eigensystem of A.)
 *    [3] J. Todd, Basic Numerical Mathematics, Vol 2: Numerical Algebra,
 *        Birkhauser, Basel, and Academic Press, New York, 1977, p. 158.
 *    [4] D.E. Rutherford, Some continuant determinants arising in
 *        physics and chemistry---II, Proc. Royal Soc. Edin., 63,
 *        A (1952), pp. 232-241. (For the eigenvalues of Givens' matrix.)
 *
 * \code
 * #include <nt2/include/functions/minij.hpp>
 * \endcode
 *
**/
//==============================================================================
// minij actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag minij_ of functor minij
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct minij_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::minij_, minij, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::minij_, minij, 3)



  template<class A0>
  typename meta::call<tag::minij_(const A0 &, typename meta::as_<double> const &)>::type
  minij(const A0& n)
  {
    return nt2::minij(n, meta::as_<double>());
  }
  template<class T, class A0>
  typename meta::call<tag::minij_(const A0 &, typename meta::as_<T> const &)>::type
  minij(const A0& n)
  {
    return nt2::minij(n, meta::as_<T>());
  }
  template<class T, class A0, class A1>
  typename meta::call<tag::minij_(const A0 &, const A1 &, typename meta::as_<T> const &)>::type
  minij(const A0& m, const A1& n)
  {
    return nt2::minij(m, n,meta::as_<T>());
  }

}

#endif
