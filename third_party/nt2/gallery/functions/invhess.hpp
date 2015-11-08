//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_INVHESS_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_INVHESS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_invhess invhess
 *
 * \par Description
 *   invhess(x,y), where x is an n-vector and y an
 *    n-1 vector, is the matrix whose lower triangle agrees with
 *    that of ones(n,1)*transconj(x) and whose strict upper triangle agrees
 *    with that of [1 y]*ones(1,n).
 *
 *    the matrix is nonsingular if x(1) ~= 0 and x(i+1) ~= y(i)
 *    for all i, and its inverse is an upper hessenberg matrix.
 *    y defaults to -x(1:n-1).
 *
 *    if n is a scalar, gallery('invhess',n) is the same
 *    as invhess(_(1, n)).
 *    References:
 *    [1] F. N. Valvi and V. S. Geroyannis, Analytic inverses and
 *        determinants for a class of matrices, IMA Journal of Numerical
 *        Analysis, 7 (1987), pp. 123-128.
 *    [2] W.-L. Cao and W. J. Stewart, A note on inverses of
 *        Hessenberg-like matrices, Linear Algebra and Appl., 76 (1986),
 *        pp. 233-240.
 *    [3] Y. Ikebe, On inverses of Hessenberg matrices, Linear Algebra
 *        and Appl., 24 (1979), pp. 93-97.
 *    [4] P. Rozsa, On the inverse of band matrices, Integral Equations
 *        and Operator Theory, 10 (1987), pp. 82-95.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/invhess.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// invhess actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag invhess_ of functor invhess
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct invhess_ :   ext::unspecified_<invhess_> { typedef  ext::unspecified_<invhess_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::invhess_, invhess, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::invhess_, invhess, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::invhess_, invhess, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::invhess_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  nt2::numel(boost::proto::child_c<0>(e));
      result_type sizee;
      sizee[0] = sizee[1] = n;
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::invhess_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename t_type::value_type                                       type;
  };
} }


#endif
