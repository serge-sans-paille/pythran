//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SVD_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct svd_ : ext::tieable_<svd_>
    {
      typedef ext::tieable_<svd_>  parent;
    };
  }

  /**
     s = svd(x)
     s = svd(x, vector_)
     s = svd(x, matrix_)
     tie(u,s,v) = svd(x, matrix_)
     tie(u,s,v) = svd(x, vector_)
     tie(u,s,v) = svd(x)
     tie(u,s,v) = svd(x,0)
     tie(u,s,v) = svd(x, econ_)
     tie(u,s,tv) = svd(x, raw_)

     Description

     The svd command computes the matrix singular value decomposition.

     s = svd(x) returns a vector of singular values.

     tie(u,s,v) = svd(x) or ie(u,s,v) = svd(x,  matrix_) produces a diagonal
     matrix s of the same dimension as x, with nonnegative diagonal
     elements in decreasing order, and unitary matrices u and v so that
     x = u*s*ctrans(v).

     tie(u,s,v) = svd(x,0) produces the "economy size" decomposition. if
     x is m-by-n with m > n, then svd computes only the first n
     columns of u and s is n-by-n.

     tie(u,s,v) = svd(x,econ_) also produces the "economy size"
     decomposition. if x is m-by-n with m >= n, it is equivalent to
     svd(x,0). for m < n, only the first m columns of v are computed
     and s is m-by-m.

     tie(u,s,tv) = svd(x,raw_) also produces the lapack direct output
     decomposition. s is a real vector of the singular values and tv is
     the transconjugate of matrix v.

     tie(u,s,v) = svd(x, vector_) returns s as a vector but v is
     not transconjugated.

     options econ_ and 0 implies s as a matrix, option raw_ implies s as a vector.

   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::svd_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
