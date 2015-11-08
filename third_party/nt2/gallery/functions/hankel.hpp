//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_HANKEL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_HANKEL_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_hankel hankel
 *
 * \par Description
 * compute a hankel matrix
 * HANKEL Hankel matrix.
 *    hankel(c,r) is a non-symmetric hankel matrix having c as its
 *    first column and r as its first row.
 *
 *    hankel(r) is a symmetric hankel matrix for real r.
 *    for a complex vector r with a real first element, t = hankel(r)
 *    returns the hermitian hankel matrix formed from r. when the
 *    first element of r is not real, the resulting matrix is hermitian
 *    off the main diagonal, i.e., t(i,j) = conj(t(j,i)) for i != j.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/hankel.hpp>
 * \endcode
 *
**/
//==============================================================================
// hankel actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag hankel_ of functor hankel
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct hankel_ : ext::unspecified_<hankel_> { typedef ext::unspecified_<hankel_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hankel_, hankel, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hankel_, hankel, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::hankel_, Domain, N, Expr>
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
  struct  size_of<tag::hankel_, Domain, 1, Expr>
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
  struct value_type < tag::hankel_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type child0;
    typedef typename child0::value_type                                    type;
  };
} }
#endif

