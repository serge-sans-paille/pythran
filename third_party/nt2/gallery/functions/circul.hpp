//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CIRCUL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CIRCUL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_circul circul
 *
 * \par Description
 *    c = circul(v) is the circulant matrix whose first row is v.
 *    a circulant matrix has the property that each row is obtained
 *    from the previous one by cyclically permuting the entries one step
 *    forward. it is a special toeplitz matrix in which the diagonals
 *    "wrap round". if v is a scalar, then c = circul(_(1, v)).
 *
 *    the eigensystem of c (n-by-n) is known explicitly. if t is an nth
 *    root of unity, then the inner product of v with w = cath(1 t t^2 ... t^(n-1))
 *    is an eigenvalue of c, and w(_(n, -1, 1)) is an eigenvector of c.
 *
 *    Reference:
 *    P. J. Davis, Circulant Matrices, John Wiley, 1977.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/circul.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// circul actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag circul_ of functor circul
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct circul_ : ext::unspecified_<circul_> { typedef ext::unspecified_<circul_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::circul_, circul, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::circul_, circul, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::circul_, circul, 3)
  template < class T> container::table<T> circul(size_t n)
  {
    return nt2::circul(nt2::_(T(1), T(n)));
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::circul_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t n =  numel(boost::proto::child_c<0>(e));
      result_type sizee;
      sizee[0] = sizee[1] = n;
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::circul_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type   type;
  };

} }
#endif

