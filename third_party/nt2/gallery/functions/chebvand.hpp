//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CHEBVAND_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CHEBVAND_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_chebvand chebvand
 *
 * \par Description
 * function C = chebvand(m,p)
 * compute a vandermonde-like matrix for the chebyshev polynomials.
 *   c = chebvand(p), where p is a vector, produces the
 *   (primal) chebyshev vandermonde matrix based on the points p:
 *      c(i,j) = t_{i-1}(p(j)), where t_{i-1} is the chebyshev
 *      polynomial of degree i-1.
 *   chebvand(m,p) is a rectangular version of
 *   chebvand(p) with m rows.
 *   special case: if p is a scalar, then p equally spaced points on
 *      [0,1] are used.

 *   Reference:
 *   [1] N. J. Higham, Stability analysis of algorithms for solving confluent
 *       Vandermonde-like systems, SIAM J. Matrix Anal. Appl., 11 (1990),
 *       pp. 23-41.
 *
 *   Nicholas J. Higham, Dec 1999.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/chebvand.hpp>
 * \endcode
 *
 **/
//==============================================================================
// chebvand actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag chebvand_ of functor chebvand
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct chebvand_ : ext::unspecified_<chebvand_> { typedef ext::unspecified_<chebvand_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chebvand_, chebvand, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chebvand_, chebvand, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::chebvand_, chebvand, 3)

  template < class T >
  BOOST_FORCEINLINE
  typename meta::call<tag::chebvand_(size_t, size_t, meta::as_<T>)>::type
  chebvand(size_t n,  size_t k)
  {
    return nt2::chebvand(n, k, meta::as_<T>());
  }

  template < class T >
  BOOST_FORCEINLINE
  typename meta::call<tag::chebvand_(size_t, meta::as_<T>)>::type
  chebvand(size_t n)
  {
    return nt2::chebvand(n, meta::as_<T>());
  }
}

#endif

