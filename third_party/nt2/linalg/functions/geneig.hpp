//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENEIG_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/linalg/functions/geneig.hpp>

namespace nt2
{
  namespace tag
  {
    struct geneig_ : ext::tieable_<geneig_>
    {
      typedef ext::tieable_<geneig_>  parent;
    };
  }

  /**
     geneig (for generalized eigen problem
     solve a*vr =  b*x*w  and ctrans(vl)*a*beta = ctrans(vl)*b*alpha
     for right (vr) and left (vl) eigenvectors
     and eigenvalues w =  alpha/beta.
     lambda is usually represented as the pair (alpha,beta), as
     there is a reasonable interpretation for beta=0, and even for both
     being zero.

     The outputs are to be complex except beta which is real if a and b are.

     The possible calls are

     1) w = geneig(a, b{, opt1});
     2) tie(alpha, beta) = geneig(a, b, alphabeta_, {opt2});
     3) tie(vr, w) = geneig(a, b{, opt1, {opt2}});
     4) tie(vr, alpha, beta) = geneig(a, b, alphabeta_, {opt2});
     5) tie(vr, w, vl) = geneig(a{, opt1, {opt2}});
     6) tie(vr, alpha, beta, vl) = geneig(a, b{, opt1, {opt2}});

     You have to include nt2/linalg/options.hpp if you use any options
     opt1 can be nt2::matrix_, nt2::vector_ or alphabeta_

     matrix_ and vector_ specify if w (or alpha and beta) is (are) to be returned as
     diagonal matrix or colon vector.
     For call 1 vector_ is the default,  for the others matrix_ is the default.
     For call 2 alphabeta_ option as option one is required as no option is call 3)

     alphabeta_ option is used to require the alpha beta form of eigenvalues
     the alpha/beta form being the default

     Algorithms
     geneig is performed using xggev LAPACK routines.

   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::geneig_, geneig, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::geneig_, geneig, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::geneig_, geneig, 3)
  NT2_FUNCTION_IMPLEMENTATION(tag::geneig_, geneig, 4)


 }

namespace nt2 { namespace ext
{
 template<class Domain, int N, class Expr>
  struct  size_of<tag::geneig_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::geneig_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
               ::child_c<Expr&,0>::value_type::value_type  intype;
    typedef typename meta::as_complex<intype>::type type;
  };
} }

#endif
