//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCHUR_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCHUR_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/sdk/meta/size_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct schur_ : ext::tieable_<schur_>
    {
      typedef ext::tieable_<schur_>  parent;
    };
  }

  /**
   * @brief Perform Schur factorization
   *
   * For any given matrix expression, performs a Schur factorization of
   * said matrix using the specified output layout for the Schur method.
   *
   *
   * possible calls are
   * t =  schur(a);
   *     if a is complex, the complex schur form is returned in matrix t.
   *     the complex schur form is upper triangular with the eigenvalues
   *     of a on the diagonal.
   *
   *     if a is real, or has only real elements two different decompositions are available.
   *     t = schur(a,real_) has the real eigenvalues on the diagonal and the
   *     complex eigenvalues in 2-by-2 blocks on the diagonal.
   *     t = schur(a,cmplx_) is triangular and is complex.
   *     t = schur(a,real_) is the default for real types entry and in this case is equivalent to
   *     t = schur(a). For complex types entry the complex form is the default and in this case
   *     t = schur(a,cmplx_) is equivalent to schur(a).
   *
   * t =  schur(a, real_);   // all a coefficients must contain real values
   * t =  schur(a, cmplx_);  // t must be able to receive complex elts
   *
   * tie(u, t) = schur(a, ...) also returns the unitary (orthogonal in the real_ case) matrix u
   *                        such that u*t*ctrans(u) ==  a
   * tie(u, t, w) = schur(a, ...) returns also the vector w containing the eigenvalues of a (w
   *                           is mandatorily complex)
   *
   *
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::schur_, schur, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::schur_, schur, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::schur_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
