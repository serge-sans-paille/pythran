//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
 **/
#ifndef NT2_SIGNAL_FUNCTIONS_UNWRAP_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_UNWRAP_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
/*!
 * \ingroup signal
 * \defgroup signal_unwrap permsn
 *    unwrap(p) unwraps radian phases p by changing absolute
 *    jumps greater than or equal to pi to their 2*pi complement.
 *    it unwraps along the first non-singleton dimension of p
 *    and leaves the first phase value along this dimension
 *    unchanged. p can be a scalar, vector, matrix, or n-d array.
 *
 *    unwrap(p,tol) where tol is a floating value uses a jump tolerance of tol rather
 *    than the default tol = pi.
 *
 *    unwrap(p,dim) or unwap(p, tol,  dim) where dim is an integer value
 *    unwraps along dimension dim using the
 *    default tolerance (resp. tol).
 *    Using small tolerances under 1.0 is not advised.
 */
namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag unwrap_ of functor unwrap
     *        in namespace nt2::tag for toolbox signal
    **/
    struct unwrap_ : ext::unspecified_<unwrap_>
    {
      typedef ext::unspecified_<unwrap_> parent;
    };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::unwrap_, unwrap, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::unwrap_, unwrap, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::unwrap_, unwrap, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::unwrap_, Domain, N, Expr>
    : meta::size_as<Expr,0>
  {};

  template <class Domain, class Expr, int N>
  struct value_type < tag::unwrap_, Domain,N,Expr>
    : meta::value_as<Expr,0>
  {};
} }

#endif
