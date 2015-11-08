//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_POLYFIT_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_POLYFIT_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief polyfit generic tag

     Represents the polyfit function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct polyfit_ : ext::tieable_<polyfit_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<polyfit_> parent;
    };
  }
  /*!
    Finds the coefficients of a polynomial p(x) of degree n that of
    degree n that best fits the data, p(x(i)) to y(i), in the least
    squares sense the data y. p is a row expression of length n+1
    containing the polynomial coefficients in descending powers:

    @code
    p(1)*x^n + p(2)*x^(n-1) +...+ p(n)*x + p(n+1).
    @endcode

    n default to numel(x)-1, to produce interpolation.

    @par Semantic:

    @code
    auto p = polyfit(x,y{,n});
    @endcode

    or

    @code
    tie(p,r,df,normr) = polyfit(x,y{,n})
    @endcode

    or

    @code
    tie(p,r,df,normr,mu) = polyfit(x,y{,n})
    @endcode


    returns the polynomial coefficients p and in the second and third options
    three other results for use with polyval to obtain error estimates
    for predictions. The triangular factor r from a qr decomposition
    of the vandermonde matrix of x, the degrees of freedom df, and
    the norm of the residuals normr.  If the data y are normal random, an
    estimate of the covariance matrix of p is (rinv*rinv')*normr^2/df,
    where rinv is the inverse of r.

    With the third option, finds the coefficients of a polynomial in
    xhat = (x-mu(1))/mu(2) where mu(1) = mean(x) and mu(2) = stdev(x). This
    centering and scaling transformation improves the numerical properties
    of both the polynomial and the fitting algorithm.

    @see @funcref{mean}, @funcref{stdev}

    @param a0

    @param a1

    @param a2 if not present default to the common numel of a0 and a1, minus one

    @return the output(s) depends of the call form
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::polyfit_, polyfit, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::polyfit_, polyfit, 2)
}

 namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::polyfit_,Domain,N,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      sizee[1] = size_t(boost::proto::child_c<2>(e))+1;
      return sizee;
    }
  };
  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::polyfit_,Domain,2,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      sizee[1] = nt2::numel(boost::proto::child_c<0>(e))+1u;
      return sizee;
    }
  };


  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::polyfit_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif
