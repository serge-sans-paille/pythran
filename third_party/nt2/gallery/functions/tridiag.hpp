//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_TRIDIAG_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_TRIDIAG_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_tridiag tridiag
 *
 * \par Description
 * tridiagonal matrix
 *  tridiag(x,y,z) is the  tridiagonal matrix with
 *  subdiagonal x, diagonal y, and superdiagonal z.
 *  if they are vectors x and z are  of dimension one less than y.
 *  but only one vector is necessary if n is not provided the other can
 *  be scalar. Be aware that if x or z is the lone vector, matrix dimension
 *  will be (length(x)+1)X(length(x)+1) (respectively with z). If
 *  y is given length(y)Xlength(y)
 *
 *  tridiag(n,c,d,e), where c, d, and e are all scalars,
 *  yields the toeplitz tridiagonal matrix of order n with subdiagonal
 *  elements c, diagonal elements d, and superdiagonal elements e. this
 *  matrix has eigenvalues: d + 2*sqrt(c*e)*cos(k*pi/(n+1)), k=1:n.
 *
 *  tridiag(n) is the same as tridiag(n,-1,2,-1),
 *  which is a symmetric positive definite m-matrix (the negative of the
 *  second difference matrix).
 *  References:
 *  [1] J. Todd, Basic Numerical Mathematics, Vol 2: Numerical Algebra,
 *      Birkhauser, Basel, and Academic Press, New York, 1977, p. 155.
 *  [2] D. E. Rutherford, Some continuant determinants arising in
 *      physics and chemistry---II, Proc. Royal Soc. Edin., 63,
 *      A (1952), pp. 232-241.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/tridiag.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// tridiag actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag tridiag_ of functor tridiag
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct tridiag_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::tridiag_, tridiag, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::tridiag_, tridiag, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::tridiag_, tridiag, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::tridiag_, tridiag, 1)

  template<class T, class I>
  typename meta::call<nt2::tag::tridiag_(const I&, nt2::meta::as_<T>) >::type
  tridiag(const I& n)
  {
    return tridiag(n, nt2::meta::as_<T>());
  }

}

#endif
