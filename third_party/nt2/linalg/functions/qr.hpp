//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_QR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_QR_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct qr_ : ext::tieable_<qr_>
    {
      typedef ext::tieable_<qr_>  parent;
    };
  }

  /**
     Syntax

     tie(q,r) = qr(a)
     tie(q,r) = qr(a,0)
     tie(x, tau) = qr(a, raw_)
     tie(x, tau, ip) = qr(a, raw_)
     tie(q,r,e) = qr(a)
     tie(q,r,e) = qr(a,matrix_)
     tie(q,r,e) = qr(a,vector_)
     tie(q,r,e) = qr(a,0)
     r = qr(a, upper_)
     x = qr(a)
     x = qr(a, 0)
     x = qr(a, raw_)

     description

     tie(q,r) = qr(a), where a is m-by-n, produces an m-by-n upper
     triangular matrix r and an m-by-m unitary matrix q so that a =
     q*r.

     tie(q,r) = qr(a,0) produces the economy-size decomposition. if m >
     n, only the first n columns of q and the first n rows of r are
     computed. if m<=n, this is the same as tie(q,r) = qr(a).

     tie(q,r,e) = qr(a) or tie(q,r,e) = qr(a,matrix_) produces unitary q,
     upper triangular r and a permutation matrix e so that a*e =
     q*r. the column permutation matrix e is chosen so that abs(diag(r)) is
     decreasing.

     tie(q,r,e) = qr(a,vector_) returns the permutation information as a
     vector instead of a matrix. that is, e is a row vector of integral values
     such that a(:,e) = q*r.

     tie(q,r,e) = qr(a,0) produces an economy-size decomposition in which
     e is a permutation vector, so that a(:,e) = q*r.

     r = qr(a, upper_) return the upper triangular matrix r

     x = qr(a) and x = qr(a,0) and x = qr(a,raw_) return a matrix x
     such that triu(x) is the upper triangular factor r.

    x = nt2::qr(b, nt2::raw_) or tie(x, tau) = nt2::qr(b, nt2::raw_) or
    tie(x, tau, ip) = nt2::qr(b, nt2::raw_)  produces the direct lapack ouputs

    option 0 which is for Matlab compatibility can be replaced by econ_
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::qr_, qr, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::qr_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
