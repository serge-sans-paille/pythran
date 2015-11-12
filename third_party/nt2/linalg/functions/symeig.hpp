//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SYMEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SYMEIG_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct symeig_ : ext::tieable_<symeig_>
    {
      typedef ext::tieable_<symeig_>  parent;
    };
  }

  /**
    symeig computes the eigenvalues and/or eigenvectors of a symetric real or
    hermitian complex input.

    symeig can be called:
    w = symeig(a) or  w = symeig(a, raw_)
    w = symeig(a, matrix_/vector_/lower_/upper_)
    w = symeig(a, matrix_/vector_,  lower_, upper_)
    tie(w, v) = symeig(a)
    tie(w, v) = symeig(a, matrix_/vector_/lower_/upper_)
    tie(w, v) = symeig(a, matrix_/vector_,  lower_/upper_)
    tie(w, v) = symeig(a, raw_)
    tie(w, v) = symeig(a, raw_)
    tie(w, v) = symeig(a, raw_, lower_/upper_)

    w will contain the eigenvalues (which are real) in vector_ or diagonal matrix_ form.
    w is always real.
    With 2 outputs default is matrix_
    With 1 output  default is vector_

    v will contain the eigenvectors in a matrix of element
    of the same type as the input elements

    lower_/upper_ determines which part of the supposed symetric/hermitian input will
    be accessed (default is upper_), the other part being never referenced.

    For instance symeig(a,lower_) and  symeig(tril(a),lower_) lead to the same result.

    with raw_ the matrices returned are the direct lapack result:
      w a vector of real eigenvalues
      v a matrix of eigenvectors
    In all raw_ calls raw_ is equivalent to vector_.
    The rationale for raw_ here is only to make obvious what are the most direct
    (so a priori efficient) calls.

    Note : with 3 inputs the 2 options can be given in reverse order
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::symeig_, symeig, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::symeig_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
