//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_KAHAN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_KAHAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>

#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_kahan kahan
 *   kahan(n,k, as_<T>) is a tridiagonal matrix with zero diagonal
 *   entries and known eigenvalues. it is singular if n is odd. about 64
 *   percent of the entries of the inverse are zero. the eigenvalues
 *   are plus and minus the numbers n-1, n-3, n-5, ..., (1 or 0).
 *   for k = 0 (the default) the matrix is unsymmetric, while for
 *   k = 1 it is symmetric. kahan(n,1) is diagonally similar
 *   to kahan(n).
 *   for odd n = 2*m+1, m+1 of the singular values are the integers
 *   sqrt((2*m+1)^2 - (2*k+1).^2), k = 0:m.
 *
 *   note:
 *   similar properties hold for tridiag(x,y,z) where
 *   y = zeros(n,1). the eigenvalues still come in plus/minus pairs but
 *   they are not known explicitly.
 *
 *   References:
 *   [1] T. Boros and P. Rozsa,  An Explicit Formula for Singular
 *       Values of the Sylvester--Kac Matrix, Linear Algebra and Appl.,
 *       421 (2007), pp. 407-416.
 *   [2] P. A. Kahan, A class of triple-diagonal matrices for test
 *   purposes, SIAM Review, 1 (1959), pp. 50-52.
 *   [3] O. Taussky and J. Todd, Another look at a matrix of Mark Kac,
 *   Linear Algebra and Appl., 150 (1991), pp. 341-360.
 *
 *   Nicholas J. Higham
 *   Copyright 1984-2008 The MathWorks, Inc.
 *   $Revision: 1.9.4.2 $
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/kahan.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// kahan actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag kahan_ of functor kahan
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct kahan_ :  ext::unspecified_<kahan_>
    {
      typedef ext::unspecified_<kahan_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::kahan_, kahan, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::kahan_, kahan, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::kahan_, kahan, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::kahan_, kahan, 4)

  template < class T> container::table<T> kahan(size_t n, size_t k)
  {
    return nt2::kahan(n, k, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::kahan_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::value(boost::proto::child_c<2>(e));
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::kahan_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                              type;
  };
} }
#endif
