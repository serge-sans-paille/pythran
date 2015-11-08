//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RANDSVD_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RANDSVD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_randsvd randsvd
 *
 * randsvd random matrix with pre-assigned singular values.
 *    a = randsvd(m, n, kappa, mode, kl, ku) is a banded random
 *    matrix of order mxn with cond(a) = kappa and singular values from the
 *    distribution mode.
 *
 *    mode may be one of the following value:
 *        1: one large singular value,
 *        2: one small singular value,
 *        3: geometrically distributed singular values,
 *        4: arithmetically distributed singular values,
 *        5: random singular values with uniformly distributed logarithm.
 *    if omitted, mode defaults to 3, and kappa defaults to sqrt(1/eps),
 *    (but if kappa is not given, a target must be : as_<type>(),  where type
 *    is the type of the output element).
 *    if mode < 0 then the effect is as for abs(mode) except that in the
 *    original matrix of singular values the order of the diagonal
 *    entries is reversed: small to large instead of large to small.
 *
 *    kl and ku are the number of lower and upper off-diagonals
 *    respectively. if they are omitted, a full matrix is produced.
 *    if only kl is present, ku defaults to kl.
 *
 *    special case: kappa < 0
 *       a is a random full symmetric positive definite matrix with
 *       cond(a) = -kappa and eigenvalues distributed according to
 *       mode. kl and ku, if present, are ignored.
 *
 *    acknowledgement:
 *    This routine is similar to the more comprehensive Fortran routine
 *    xLATMS in the following reference:
 *
 *    Reference:
 *    J. W. Demmel and A. McKenney, A test matrix generation suite,
 *    LAPACK Working Note #9, Courant Institute of Mathematical
 *    Sciences, New York, 1989.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/randsvd.hpp>
 * \endcode
 *
 **/
//==============================================================================
// randsvd actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag randsvd_ of functor randsvd
     *        in namespace nt2::tag for toolbox algebra
     **/
     struct randsvd_ : ext::unspecified_<randsvd_>
    {
      typedef ext::unspecified_<randsvd_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::randsvd_, randsvd, 6)
  NT2_FUNCTION_IMPLEMENTATION(tag::randsvd_, randsvd, 5)
  NT2_FUNCTION_IMPLEMENTATION(tag::randsvd_, randsvd, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::randsvd_, randsvd, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::randsvd_, randsvd, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::randsvd_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = boost::proto::child_c<0>(e);
      sizee[1] = boost::proto::child_c<1>(e);
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::randsvd_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,2>::type                 tmp_type;
    typedef typename  meta::strip<tmp_type>::type                                         type;
  };
} }

#endif

