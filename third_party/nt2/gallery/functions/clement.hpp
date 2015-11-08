//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CLEMENT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CLEMENT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_clement clement
 *   clement(n,k, as_<T>) is a tridiagonal matrix with zero diagonal
 *   entries and known eigenvalues. it is singular if n is odd. about 64
 *   percent of the entries of the inverse are zero. the eigenvalues
 *   are plus and minus the numbers n-1, n-3, n-5, ..., (1 or 0).
 *   for k = 0 (the default) the matrix is unsymmetric, while for
 *   k = 1 it is symmetric. clement(n,1) is diagonally similar
 *   to clement(n).
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
 *   [2] P. A. Clement, A class of triple-diagonal matrices for test
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
 * #include <nt2/include/functions/clement.hpp>
 * \endcode
 *
 *
**/
//==============================================================================
// clement actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag clement_ of functor clement
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct clement_ :  ext::unspecified_<clement_>
    {
      typedef ext::unspecified_<clement_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::clement_, clement, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::clement_, clement, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::clement_, clement, 3)

  template < class T> container::table<T> clement(size_t n, size_t k)
  {
    return nt2::clement(n, k, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::clement_, Domain, N, Expr>
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

  template <class Domain, class Expr, int N>
  struct value_type < tag::clement_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,2>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  boost::dispatch::meta::semantic_of<tmp1_type>::type tmp2_type;
    typedef typename  tmp2_type::type                                          type;
  };
} }
#endif
