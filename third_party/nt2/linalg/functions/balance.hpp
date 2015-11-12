//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BALANCE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BALANCE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct balance_ : ext::unspecified_<factorization::balance_>
      {
        typedef ext::unspecified_<factorization::balance_> parent;
      };
    }

    struct balance_ :  ext::tieable_<balance_>
    {
      typedef ext::tieable_<balance_>  parent;
    };
  }

  /**
   * @brief Perform Balance factorization
   *
   * For any given matrix expression a, performs a
   * balance diagonal scaling to improve eigenvalue accuracy.
   *
   *     tie(t,b) = balance(a) finds a similarity transformation t such
   *     that b = inv(t)*a*t has, as nearly as possible, approximately equal
   *     row and column norms.  t is a permutation of a diagonal matrix
   *     whose elements are integer powers of two so that the balancing
   *     doesn't introduce any round-off error.
   *
   *     b = balance(a) returns the balanced matrix b.
   *
   *     tie(s,p,b) = balance(a) returns the scaling vector s and the
   *     permutation vector p separately.  the transformation t and
   *     balanced matrix b are obtained from a,s,p by
   *        t(_,p) = diag(s), b(p,p) = from_diag(1./s)*a*from_diag(s).
   *
   *     to scale a without permuting its rows and columns, use
   *     the syntax balance(a, no_perm_).
   *     to do nothing(!), use the syntax balance(a, none_).
   *     (this can be useful to see the impact while retaining the code).
   *
   *     tie(s,p,b) = balance(a), [t,b] = balance(a) and b = balance(a)
   *     are respectively equivalent to
   *     tie(s,p,b) = balance(a, both_), tie(t,b) = balance(a, both_)
   *     and b = balance(a, both_).
   *
   *     balance uses xgebal and xgebak lapack routines
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::balance_, balance, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::balance_, balance, 2)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::balance_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
