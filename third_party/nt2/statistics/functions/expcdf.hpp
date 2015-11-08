//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_EXPCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_EXPCDF_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/utility/max_extent.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief expcdf generic tag

     Represents the expcdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct expcdf_ : ext::tieable_<expcdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<expcdf_> parent;
    };
    struct expcdf0_: ext::elementwise_<expcdf0_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<expcdf0_> parent;
    };
  }
  /*!
    exponential  cumulative distribution

    @par Semantic:

    For every table expression

    @code
    T0 r = expcdf(a0, lambda);
    @endcode

    is similar to:

    @code
    T0 r =  -nt2::expm1(-max(0, a0/lambda));
    @endcode

    @see @funcref{expfit}, @funcref{expm1}
    @param a0
    @param a1 optional mean default to 1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf0_, expcdf, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf0_, expcdf, 1)
  /*!
    exponential  cumulative distribution with bounds estimates

    @par Semantic:

    For every table expression

    @code
    tie(r, rlo, rup) = expcdf(a0, lambda, cov, alpha);
    @endcode

    Returns r = expcdf(a0, lambda), but also produces confidence
    bounds for r when the input parameter lambda is an estimate.  cov
    is the variance of the estimated lambda.  alpha has a default
    value of 0.05, and specifies 100*(1-alpha)% confidence bounds.
    rlo and rup are tables of the same size as a0 containing the lower
    and upper confidence bounds.  the bounds are based on a normal
    approximation for the distribution of the log of the estimate of
    lambda.

    @see @funcref{expfit}, @funcref{expm1}
    @param a0
    @param a1 mean estimate
    @param a2 variance of the estimated a1
    @param a3 optional confidence bound (default to 0.05)

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf_, expcdf, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf_, expcdf, 3)
}



namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::expcdf_,Domain,N,Expr> // N =  3 or 4
  {
    typedef typename  boost::proto::result_of::child_c<Expr&,0>
                      ::value_type::extent_type                     ext0_t;
    typedef typename  boost::proto::result_of::child_c<Expr&,1>
                      ::value_type::extent_type                     ext1_t;

    typedef typename utility::result_of::max_extent< ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {

      return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                        nt2::extent(boost::proto::child_c<1>(e)));
    }
  };
  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::expcdf_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<tag::expcdf_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
