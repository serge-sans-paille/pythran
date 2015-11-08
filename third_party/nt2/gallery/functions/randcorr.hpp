//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RANDCORR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RANDCORR_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/sdk/meta/value_as.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_randcorr randcorr
 *
 *    randcorr(n) is a random n-by-n correlation matrix with
 *    random eigenvalues from a uniform distribution.
 *    a correlation matrix is a symmetric positive semidefinite matrix with
 *    1s on the diagonal (see corrcoef).
 *
 *    randcorr(x) produces a random correlation matrix
 *    having eigenvalues given by the vector x, where length(x) > 1.
 *    x must have nonnegative elements summing to length(x).
 *
 *    an additional argument, k, can be supplied.
 *    for k = 0 (the default) the diagonal matrix of eigenvalues is initially
 *        subjected to a random orthogonal similarity transformation and then
 *        a sequence of givens rotations is applied.
 *    for k = 1, the initial transformation is omitted. this is much faster,
 *        but the resulting matrix may have some zero entries.
 *
 *   References:
 *   [1] R. B. Bendel and M. R. Mickey, Population correlation matrices
 *       for sampling experiments, Commun. Statist. Simulation Comput.,
 *       B7 (1978), pp. 163-182.
 *   [2] P. I. Davies and N. J. Higham, Numerically stable generation of
 *       correlation matrices and their factors, BIT, 40 (2000), pp. 640-651.
 *
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/randcorr.hpp>
 * \endcode
 *
 **/
//==============================================================================
// randcorr actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag randcorr_ of functor randcorr
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct randcorr0_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
     struct randcorr_ : ext::unspecified_<randcorr_>
    {
      typedef ext::unspecified_<randcorr_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::randcorr_, randcorr, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::randcorr_, randcorr, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::randcorr_, randcorr, 1);
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::randcorr_, Domain, N, Expr> : meta::boxed_size<Expr, 3>
  {};

  template <class Domain, class Expr, int N>
  struct value_type < tag::randcorr_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename meta::strip<t_type>::type                         tt_type;
    typedef typename tt_type::value_type                                       type;
  };
} }

#endif

