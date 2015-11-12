//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_BANDRED_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_BANDRED_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_bandred bandred
 *    band reduction by two-sided unitary transformations.
 *    b = bandred(a, kl, ku) is a matrix unitarily equivalent to a
 *    with lower bandwidth kl and upper bandwidth ku
 *    (i.e. b(i,j) = 0 if i > j+kl or j > i+ku).
 *    the reduction is performed using householder transformations.
 *    if ku is omitted it defaults to kl.
 *
 *    called by randsvd.
 *    this is a `standard' reduction.  cf. reduction to bidiagonal form
 *    prior to computing the svd.  this code is a little wasteful in that
 *    it computes certain elements which are immediately set to zero!
 *
 *    Reference:
 *    G. H. Golub and C. F. Van Loan, Matrix Computations, third
 *    edition, Johns Hopkins University Press, Baltimore, Maryland,
 *    1996, Sec. 5.4.3.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/bandred.hpp>
 * \endcode
 *
 **/
//==============================================================================
// bandred actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag bandred_ of functor bandred
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct bandred_ : ext::unspecified_<bandred_>
    {
      typedef ext::unspecified_<bandred_> parent;
    };
}

  NT2_FUNCTION_IMPLEMENTATION(tag::bandred_, bandred, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::bandred_, bandred, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::bandred_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee = extent(nt2::numel(boost::proto::child_c<0>(e)));
      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::bandred_, Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>::type      tmp_type;
    typedef typename  meta::strip<tmp_type>::type                            s_type;
    typedef typename  s_type::value_type                                       type;
  };
} }

#endif

