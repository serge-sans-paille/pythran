//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_POLY_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_POLY_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/poly.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct poly_ : ext::unspecified_<factorization::poly_>
      {
        typedef ext::unspecified_<factorization::poly_> parent;
      };
    }

    struct poly_ :  ext::unspecified_<poly_>
    {
      typedef ext::unspecified_<poly_>  parent;
    };
  }

  /**
   * @brief Perform characteristic polynomial computation
   *
   * poly(a), when a is an n by n matrix, is a row vector with
   * n+1 elements which are the coefficients of the
   * characteristic polynomial, det(lambda*eye(size(a)) - a) .
   *
   * poly(v), when v is a vector, is a vector whose elements are
   * the coefficients of the polynomial whose roots are the
   * elements of v . for vectors, roots and poly are inverse
   * functions of each other, up to ordering, scaling, and
   * roundoff error.
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::poly_, poly, 1)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::poly_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type A0;
    typedef _2D                                             result_type;
    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      sizee[1] = length( boost::proto::child_c<0>(e))+1;
      return sizee;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::poly_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
