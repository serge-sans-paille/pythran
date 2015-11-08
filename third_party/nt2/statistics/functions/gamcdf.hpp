//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GAMCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GAMCDF_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/utility/max_extent.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gamcdf generic tag

     Represents the gamcdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gamcdf_ : ext::tieable_<gamcdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<gamcdf_> parent;
    };
    struct gamcdf0_: ext::elementwise_<gamcdf0_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<gamcdf0_> parent;
    };
  }
  /*!
    gamma  cumulative distribution

    @par Semantic:

    For every table expressions and optional scalars shape and scale

    @code
    auto r = gamcdf(a0, shape, scale);
    @endcode

    is similar to:

    @code
    auto r = gammainc(shape, a0/scale);
    @endcode

    Some papers refer to the gamma distribution with a single
    parameter.  This corresponds to the default of scale = 1.
    shape has no default.

    @see @funcref{gammainc}
    @param a0
    @param a1 shape
    @param a2 optional scale (default to 1)

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf0_, gamcdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf0_, gamcdf, 2)

  /*!
    gamma  cumulative distribution

    @par Semantic:

    For every table expressions and optional scalar m

    @code
    tie(r, rlo, rup) = expcdf(a0, shape, scale, cov, alpha);
    @endcode

    Returns r = gammacdf(a0, shape, scale), but also produces
    confidence bounds for r when the input parameter lambda is an
    estimate.  cov is the variance of the estimated m.  alpha has a
    default value of 0.05, and specifies 100*(1-alpha)% confidence
    bounds.  rlo and rup are tables of the same size as a0 containing
    the lower and upper confidence bounds.

    @see @funcref{gammainc}
    @param a0
    @param a1  shape estimate
    @param a2  optional scale estimate (default to 1)
    @param a3 variance of the estimated a1
    @param a4 optional confidence bound (default to 0.05)

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf_, gamcdf, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::gamcdf_, gamcdf, 4)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<tag::gamcdf_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term0;
    typedef typename meta::strip<seq_term0>::type::extent_type          ext0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::type seq_term1;
    typedef typename meta::strip<seq_term1>::type::extent_type          ext1_t;
    typedef typename boost::proto::result_of::child_c<Expr&,2>::type seq_term2;
    typedef typename meta::strip<seq_term2>::type::extent_type          ext2_t;

    typedef typename utility::result_of::max_extent<ext2_t, ext1_t, ext0_t>::type     result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
     return utility::max_extent(nt2::extent(boost::proto::child_c<0>(e)),
                       nt2::extent(boost::proto::child_c<1>(e)),
                       nt2::extent(boost::proto::child_c<2>(e)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::gamcdf_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

} }

#endif
