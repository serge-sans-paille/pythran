//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_EXPO_BASE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_EXPO_BASE_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_nan.hpp>
#endif
#include <boost/simd/arch/common/detail/scalar/expo_reduction.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace detail
{
  template< typename A0
          , typename Tag
          , typename Style
          , typename base_A0 = bd::scalar_of_t<A0>
          >
  struct exponential
  {};

  template<typename A0, typename Tag>
  struct exponential< A0, Tag, tag::not_simd_type, double>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    // compute exp(ax) where a is 1, 2 or ten depending on Tag
    static BOOST_FORCEINLINE A0 expa(A0 a0) BOOST_NOEXCEPT
    {
      if (reduc_t::isgemaxlog(a0)) return Inf<A0>();
      if (reduc_t::isleminlog(a0)) return Zero<A0>();
     #ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return a0;
     #endif
      A0 hi = Zero<A0>(), lo = Zero<A0>(), x = Zero<A0>();
      A0 k = reduc_t::reduce(a0, hi, lo, x);
      A0 c = reduc_t::approx(x);
      c = reduc_t::finalize(x, c, hi, lo);
      return  ldexp(c, toint(k));
    }
  };

  template<typename A0, typename Tag>
  struct exponential< A0, Tag, tag::not_simd_type, float>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    // compute exp(ax) where a is 1, 2 or ten depending on Tag
    static BOOST_FORCEINLINE A0 expa(A0 a0) BOOST_NOEXCEPT
    {

      if (reduc_t::isgemaxlog(a0)) return Inf<A0>();
      if (reduc_t::isleminlog(a0)) return Zero<A0>();
    #ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return a0;
    #endif
      A0 x;
      A0 k = reduc_t::reduce(a0, x);
      x = reduc_t::approx(x);
      return  ldexp(x, toint(k));
    }
  };
} } }
#endif
