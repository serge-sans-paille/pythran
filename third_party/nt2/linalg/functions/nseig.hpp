//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NSEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NSEIG_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2
{
  namespace tag
  {
    struct nseig_ : ext::tieable_<nseig_>
    {
      typedef ext::tieable_<nseig_>  parent;
    };
  }

  /**
     nseig (for non necesserily symetric eigen problem
     solve a*vr =  w*x and vr*a = vl for right (vr) and left (vl) eigenvectors
     and eigenvalues w.

     As a is not supposed symetric the outputs are to be complex

     The possible calls are

     1) w = nseig(a{, opt1, {opt2}});
     2) tie(vr, w) = nseig(a{, opt1, {opt2}});
     3) tie(vr, w, vl) = nseig(a{, opt1, {opt2}});

     You have to include nt2/linalg/options.hpp if you use any options
     opt1 can be nt2::matrix_, nt2::vector_,  nt2::balance,  nt2::no_balance_
     opt2 can be nt2::balance_,  nt2::no_balance_ and then opt1 is to be in  nt2::matrix_, nt2::vector_

     matrix_ and vector_ specify if w is to be returned as a diagonal matrix or a colon vector.
     For call 1 vector_ is the default,  for the others matrix_ is the default.
     (of course from_diag and diag_of can be used to pass from one representation to the other)

     balance_ and no_balance_ specify if a balancing of the input matrix has to be
     done prior to computation. Default is no_balance_ (contrarily to matlab eig)

     Algorithms
     nseig is performed using xgeev LAPACK routines and balancing is done with xgebal and xgebak LAPACK
     routines with job = 'B' (permutation and scaling enabled)

  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::nseig_, nseig, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::nseig_, nseig, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::nseig_, nseig, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::nseig_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::nseig_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
               ::child_c<Expr&,0>::value_type::value_type  intype;
    typedef typename meta::as_complex<intype>::type type;
  };

} }

#endif
