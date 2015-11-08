//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_RANDCOLU_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_RANDCOLU_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/sdk/meta/value_as.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_randcolu randcolu
 *
 * randcolu random matrix with normalized columns and specified singular values.
 *    a = randcolu(n) is a random n-by-n matrix with columns of
 *    unit 2-norm, with random singular values whose squares are from a
 *    uniform distribution.  randcolu(n,m), where m >= n,
 *    produces an m-by-n matrix.
 *    a'*a is a correlation matrix of the form produced by
 *    randcorr(n).
 *
 *    randcolu(x), where x is an n-vector (n > 1), produces
 *    a random n-by-n matrix having singular values given by the vector x.
 *    x must have nonnegative elements whose sum of squares is n.
 *    randcolu(x,m), where m >= n, produces an m-by-n matrix.
 *    randcolu(x,m,k) provides a further option:
 *    for k = 0 (the default) diag(x) is initially subjected to a random
 *        two-sided orthogonal transformation and then a sequence of
 *        givens rotations is applied.
 *    for k = 1, the initial transformation is omitted. this is much faster,
 *        but the resulting matrix may have zero entries.
 *
 *   Reference:
 *   P. I. Davies and N. J. Higham, Numerically stable generation of
 *   correlation matrices and their factors, BIT, 40 (2000), pp. 640-651.
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/randcolu.hpp>
 * \endcode
 *
 **/
//==============================================================================
// randcolu actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag randcolu_ of functor randcolu
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct randcolu0_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
     struct randcolu_ : ext::unspecified_<randcolu_>
    {
      typedef ext::unspecified_<randcolu_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::randcolu_, randcolu, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::randcolu_, randcolu, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::randcolu_, randcolu, 1);

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::randcolu_, Domain, N, Expr> : meta::boxed_size<Expr, 3>
  {};

  template <class Domain, class Expr, int N>
  struct value_type < tag::randcolu_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename meta::strip<t_type>::type                         tt_type;
    typedef typename tt_type::value_type                                       type;
  };


} }

#endif

