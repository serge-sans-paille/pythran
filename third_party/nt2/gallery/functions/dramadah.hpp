//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_DRAMADAH_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_DRAMADAH_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_dramadah dramadah
 *
 * \par Description
 * function A = dramadah(n, k)
 * dramadah matrix of zeros and ones with large determinant or inverse.
 *   a = dramadah(n,k) is an n-by-n (0,1) matrix for which
 *   mu(a) = norm(inv(a),'fro') or det(a) is relatively large.
 *
 *   k = 1: (default)
 *      a is toeplitz, with abs(det(a)) = 1, and mu(a) > c(1.75)^n,
 *      where c is a constant. inv(a) has integer entries.
 *   k = 2:
 *      a is upper triangular and toeplitz. inv(a) has integer entries.
 *   k >= 3:
 *      a has maximal determinant among (0,1) lower hessenberg matrices.
 *      det(a) = the n'th fibonacci number. a is toeplitz.
 *      the eigenvalues have an interesting distribution in the complex
 *      plane.
 *
 *   an anti-hadamard matrix a is a matrix with elements 0 or 1 for
 *   which mu(a) = norm(inv(a),'fro') is maximal.  for k = 1,2 this function
 *   returns matrices with mu(a) relatively large, though not necessarily
 *   maximal.

 *   References:
 *   [1] R. L. Graham and N. J. A. Sloane, Anti-Hadamard matrices,
 *       Linear Algebra and Appl., 62 (1984), pp. 113-137.
 *   [2] L. Ching, The maximum determinant of an nxn lower Hessenberg
 *       (0,1) matrix, Linear Algebra and Appl., 183 (1993), pp. 147-153.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/dramadah.hpp>
 * \endcode
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag dramadah_ of functor dramadah
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct dramadah_ :  ext::unspecified_<dramadah_>
    {
      typedef ext::unspecified_<dramadah_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::dramadah_, dramadah, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::dramadah_, dramadah, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::dramadah_, dramadah, 3)

  template < class T > container::table<T> dramadah(size_t n,  size_t k)
  {
    return nt2::dramadah(n, k, meta::as_<T>());
  }
  template < class T > container::table<T> dramadah(size_t n)
  {
    return nt2::dramadah(n, size_t(1), meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::dramadah_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  boost::proto::child_c<0>(e);
      result_type sizee;
      sizee[0] = sizee[1] = n;
      return sizee;
    }
  };

  template <class Domain, class Expr,  int N>
  struct value_type < tag::dramadah_, Domain,N,Expr>
  {
    typedef double type;
  };

  template <class Domain, class Expr>
  struct value_type < tag::dramadah_, Domain,4,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,2>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename t_type::type                                             type;
  };
} }
#endif
