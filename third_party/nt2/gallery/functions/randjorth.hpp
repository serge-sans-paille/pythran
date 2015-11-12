//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RANDJORTH_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RANDJORTH_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_randjorth randjorth
 *
 *    a = randjorth(n) produces a random n-by-n j-orthogonal
 *    matrix a, where j = blkdiag(eye(ceil(n/2)),-eye(floor(n/2))) and
 *    cond(a) is sqrt(1/eps).
 *    j-orthogonality means that a'*j*a = j, and such matrices are sometimes
 *    called hyperbolic or pseudo-orthogonal.
 *
 *    a = randjorth(p,q,as_<T>()), where p > 0 and q > 0 produces a random
 *    (p+q)-by-(p+q) j-orthogonal matrix a, where j = blkdiag(eye(p),-eye(q))
 *    and cond(a) is sqrt(1/eps<T>()).
 *
 *    a = randjorth(p,q,c) specifies cond(a) as c.
 *
 *    a = randjorth(p,q,c,symm) enforces symmetry if symm is
 *    nonzero. a symmetric positive definite matrix is produced.
 *
 *    Reference:
 *    N. J. Higham, J-orthogonal matrices: Properties and generation,
 *    SIAM Rev., 45(3) (2003), pp. 504-519.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/randjorth.hpp>
 * \endcode
 *
 **/
//==============================================================================
// randjorth actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag randjorth_ of functor randjorth
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct randjorth_ : ext::unspecified_<randjorth_>
    {
      typedef ext::unspecified_<randjorth_> parent;
    };
}

  NT2_FUNCTION_IMPLEMENTATION(tag::randjorth_, randjorth, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::randjorth_, randjorth, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::randjorth_, randjorth, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::randjorth_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = nt2::numel(boost::proto::child_c<0>(e));
      sizee[1] = nt2::numel(boost::proto::child_c<1>(e));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::randjorth_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,N-3>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                              s_type;
    typedef typename  s_type::value_type                                         type;
  };
} }

#endif

