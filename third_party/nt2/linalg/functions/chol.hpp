//==============================================================================
//         Copyright 2014                 Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CHOL_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct chol_ : ext::tieable_<chol_>
    {
      typedef ext::tieable_<chol_>  parent;
    };
  }

  /**
     @brief Cholevski factorization of an hermitian
     (symetric in the real case) positive definite matrix.

     u = chol(a)
     l = chol(a,lower_)
     u = chol(a,upper_)
     tie(u,p) = chol(a)
     tie(l,p) = chol(a,lower_)
     tie(u,p) = chol(a,upper_)
     tie(x,p) = chol(a,raw_)
     tie(x,p) = chol(a,raw_, lower_)
     tie(x,p) = chol(a,raw_, upper_

     The three first calls assert if a is not positive definite.
     with "lapack info is not zero" message

     The three last call return a (p-1)X(p-1) matrix where p is
     the dimension of the smallest not positive definite minor of a.
     Then r (resp. l) gives the factor of the preeceding minor.

     upper_ (resp. lower_) indicates that only the upper (resp. lower)
     part of the a storage are referenced. Default is upper_.
     This also means that the  hermitianity (symetry in the real case)
     of the matrix is never tested.

     The options tags are in nt2 namespace.

     If the factorization is completed  a = ctrans(u)*u or
     a = l*ctrans(l) according to the option chosen.

     The call involving raw_ return the direct lapack output, the matrix
     returned is a square matrix the pertinent result is stored in the
     upper (with default or upper_ option) triangular part (resp. lower
     with lower_ option). p contains 0 is the input is positive definite
     or as defined above. The pertinent extractions being then
     u = triu(x(_(1, p-1), _(1, p-1)) or l =  tril(x(_(1, p-1), _(1, p-1))
     (p is the 'lapack info')

     Note : with 3 input paraleters the oder of the 2 options can be
     reversed
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_, chol, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::chol_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
