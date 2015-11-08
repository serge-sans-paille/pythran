//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LU_HPP_INCLUDED

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
    struct lu_ : ext::tieable_<lu_>
    {
      typedef ext::tieable_<lu_>  parent;
    };
  }

  /**
     y = lu(a)
     tie(l,u) = lu(a)
     tie(l,u) = lu(a, raw_)
     tie(l,u,p) = lu(a)
     tie(l,u,p) = lu(a,vector_/matrix_)


     the lu function expresses a matrix a as the product of two
     essentially triangular matrices, one of them a permutation of a
     lower triangular matrix and the other an upper triangular
     matrix. the factorization is often called the LU factorization.
     Input matrix a can be rectangular.

     y = lu(a) returns matrix y that is the direct first output from
     the LAPACK  d/sgetrf or z/cgetrf routines. the permutation matrix p is lost.

     tie(y, ls) = lu(a, raw_) returns matrix y that is the output
     from the LAPACK d/sgetrf or z/cgetrf routines. Care that the
     permutation vector ls is in Lapack Swap lines form.

     tie(l,u) = lu(a) returns an upper triangular matrix in u and a
     permuted lower triangular matrix in l such that a = l*u. return
     value l is a product of lower triangular and permutation
     matrices.

     tie(l,u,p) = lu(a) or tie(l,u,p) = lu(a,matrix_) returns an upper
     triangular matrix in u, a lower triangular matrix l with a unit
     diagonal, and a permutation matrix p, such that l*u = p*a.

     tie(l,u,ip) = lu(a,vector_) returns the permutation information
     in a vector of integers ip such that l*u = a(ip, _).

     except raw_ option that does not exist for Matlab the syntax
     is quite identical as defined by Matlab lu for dense matrices.

  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::lu_, lu, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::lu_, lu, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::lu_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
