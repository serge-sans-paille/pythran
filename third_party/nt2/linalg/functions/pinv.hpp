//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_PINV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_PINV_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/include/functions/issquare.hpp>

/*!
 * @brief inv  pseudo-inverse of matrix.
 * pinv(x) is the pseudo-inverse of the matrix expression x.
 *
 * x = pinv(a) produces a matrix x of the same dimensions
 * as trans(a) so that a*x*a = a, x*a*x = x and a*x and x*a
 * are hermitian. the computation is based on svd(a) and any
 * singular values less than a tolerance are treated as zero.
 * the default tolerance is max(size(a)) * norm(a) * eps<class(a)> .
 *
 * pinv(a,tol) uses the tolerance tol instead of the default.
 *
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag pinv_ of functor pinv
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct pinv_ :  ext::unspecified_<pinv_> { typedef ext::unspecified_<pinv_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::pinv_, pinv, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::pinv_, pinv, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::pinv_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee = boost::proto::child_c<0>(e).extent();
      std::swap(sizee[0], sizee[1]);
      return sizee;
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::pinv_, Domain,N,Expr>
  : meta::value_as<Expr,0>
 {};
} }

#endif

