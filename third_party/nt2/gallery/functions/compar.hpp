//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_COMPAR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_COMPAR_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/table/table.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_compar compar
 *
 * \par Description
 *    c = compar(v) is the comparant matrix whose first row is v.
 *    a comparant matrix has the property that each row is obtained
 *    from the previous one by cyclically permuting the entries one step
 *    forward. it is a special toeplitz matrix in which the diagonals
 *    "wrap round". if v is a scalar, then c = compar(_(1, v)).
 *
 *    the eigensystem of c (n-by-n) is known explicitly. if t is an nth
 *    root of unity, then the inner product of v with w = cath(1 t t^2 ... t^(n-1))
 *    is an eigenvalue of c, and w(_(n, -1, 1)) is an eigenvector of c.
 *
 *    Reference:
 *    P. J. Davis, Comparant Matrices, John Wiley, 1977.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/compar.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// compar actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag compar_ of functor compar
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct compar_ : ext::unspecified_<compar_> { typedef ext::unspecified_<compar_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compar_, compar, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compar_, compar, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::compar_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = nt2::size(boost::proto::child_c<0>(e), 1);
      sizee[1] = nt2::size(boost::proto::child_c<0>(e), 2);
      return sizee;
    }
  };


  template <class Domain, class Expr, int N>
  struct value_type < tag::compar_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type   type;
  };

} }
#endif

