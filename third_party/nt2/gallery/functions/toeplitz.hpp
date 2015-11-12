//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_TOEPLITZ_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_TOEPLITZ_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_toeplitz toeplitz
 *
 * \par Description
 * compute a toeplitz matrix
 * TOEPLITZ Toeplitz matrix.
 *    toeplitz(c,r) is a non-symmetric toeplitz matrix having c as its
 *    first column and r as its first row.
 *
 *    toeplitz(r) is a symmetric toeplitz matrix for real r.
 *    for a complex vector r with a real first element, t = toeplitz(r)
 *    returns the hermitian toeplitz matrix formed from r. when the
 *    first element of r is not real, the resulting matrix is hermitian
 *    off the main diagonal, i.e., t(i,j) = conj(t(j,i)) for i != j.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/toeplitz.hpp>
 * \endcode
 *
**/
//==============================================================================
// toeplitz actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag toeplitz_ of functor toeplitz
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct toeplitz_ : ext::unspecified_<toeplitz_> { typedef ext::unspecified_<toeplitz_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toeplitz_, toeplitz, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::toeplitz_, toeplitz, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::toeplitz_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] =  numel(boost::proto::child_c<0>(e));
      sizee[1] =  numel(boost::proto::child_c<1>(e));
      return sizee;
    }
  };
  template<class Domain, class Expr>
  struct  size_of<tag::toeplitz_, Domain, 1, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] =  numel(boost::proto::child_c<0>(e));
      sizee[1] =  sizee[0];
      return sizee;
    }
  };

  template <class Domain, class Expr,  int N>
  struct value_type < tag::toeplitz_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type child0;
    typedef typename child0::value_type                                    type;
  };
} }
#endif

