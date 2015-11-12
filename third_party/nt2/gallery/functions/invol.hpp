//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_INVOL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_INVOL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_invol invol
 *
 * \par Description
 * invol  involutory matrix.
 *    a =invol(n) is an n-by-n involutory (a*a = eye(n))
 *    and ill-conditioned matrix. it is a diagonally scaled version
 *    of hilb(n).
 *
 *    note: b = (eye(n)-a)/2 and b = (eye(n)+a)/2 are
 *    idempotent (b*b = b).
 *
 *    Reference:
 *    A. S. Householder and J. A. Carpenter, The singular values
 *    of involutory and of idempotent matrices,
 *    Numer. Math. 5 (1963), pp. 234-237.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/invol.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/
//==============================================================================
// invol actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag invol_ of functor invol
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct invol_ :   ext::unspecified_<invol_> { typedef  ext::unspecified_<invol_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::invol_, invol, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::invol_, invol, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::invol_, Domain, N, Expr>
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
  struct value_type < tag::invol_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename t_type::type                                             type;
  };
} }


#endif
