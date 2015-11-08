//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_CHEBSPEC_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_CHEBSPEC_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_chebspec chebspec
 *
 * \par Description
 * compute a  chebyshev spectral differentiation matrix.
 *  c = chebspec(n,k) is a chebyshev spectral
 *     differentiation matrix of order n.  k = 0 (the default) or 1.
 *  for k = 0 ("no boundary conditions"), c is nilpotent, with
 *     mpower(c, n) = 0 and it has the null vector ones(n,1).
 *     c is similar to a jordan block of size n with eigenvalues zero.
 *  for k = 1, c is nonsingular and well conditioned, and its
 *     eigenvalues have negative real parts.
 *  for both k, the computed eigenvector matrix x from eig is
 *     ill-conditioned (mesh(real(x)) is interesting).
 *
 *  References:
 *  [1] C. Canuto, M. Y. Hussaini, A. Quarteroni and T. A. Zang,
 *      Spectral Methods in Fluid Dynamics, Springer-Verlag, Berlin,
 *      1988, p. 69.
 *  [2] L. N. Trefethen and M. R. Trummer, An instability phenomenon in
 *      spectral methods, SIAM J. Numer. Anal., 24 (1987), pp. 1008-1023.
 *  [3] D. Funaro, Computing the inverse of the Chebyshev collocation
 *      derivative, SIAM J. Sci. Stat. Comput., 9 (1988), pp. 1050-1057.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/chebspec.hpp>
 * \endcode
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag chebspec_ of functor chebspec
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct chebspec_ :  ext::unspecified_<chebspec_>
    {
      typedef ext::unspecified_<chebspec_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::chebspec_, chebspec, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::chebspec_, chebspec, 3)

  template < class T > container::table<T> chebspec(size_t n,  size_t k)
  {
    return nt2::chebspec(n, k, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::chebspec_, Domain, N, Expr>
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

  template <class Domain, class Expr,  int N>
  struct value_type < tag::chebspec_, Domain,N,Expr>
  {
    typedef double type;
  };

  template <class Domain, class Expr>
  struct value_type < tag::chebspec_, Domain,4,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,2>::type      tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type   t_type;
    typedef typename t_type::type                                             type;
  };
} }
#endif
