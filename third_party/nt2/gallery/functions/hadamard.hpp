//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_HADAMARD_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_HADAMARD_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_hadamard hadamard
 *
 * \par Description
 * function C = hadamard(m,p)
 * compute a vandermonde-like matrix for the chebyshev polynomials.
 *   c = hadamard(p), where p is a vector, produces the
 *   (primal) chebyshev vandermonde matrix based on the points p:
 *      c(i,j) = t_{i-1}(p(j)), where t_{i-1} is the chebyshev
 *      polynomial of degree i-1.
 *   hadamard(m,p) is a rectangular version of
 *   hadamard(p) with m rows.
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
 * #include <nt2/include/functions/hadamard.hpp>
 * \endcode
 *
 **/
//==============================================================================
// hadamard actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag hadamard_ of functor hadamard
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct hadamard_ : ext::unspecified_<hadamard_> { typedef ext::unspecified_<hadamard_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hadamard_, hadamard, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hadamard_, hadamard, 2)

  template < class T > container::table<T> hadamard(size_t n)
  {
    return nt2::hadamard(n, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::hadamard_, Domain, N, Expr>
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
  struct value_type < tag::hadamard_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename t_type::type                                             type;
  };
} }
#endif

