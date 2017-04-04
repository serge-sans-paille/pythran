//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_REMQUO_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/fms.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( remquo_
                          , (typename A0)
                          , bd::cpu_
                          , bd::generic_<bd::floating_<A0> >
                          , bd::generic_<bd::floating_<A0> >
                          )
  {
    using quo_t = bd::as_integer_t<A0, signed>;
    using result_type = std::pair<A0,quo_t>;

    BOOST_FORCEINLINE std::pair<A0, quo_t> operator() ( A0 const& a0, A0 const& a1
                                      ) const BOOST_NOEXCEPT
    {
      A0 const d = nearbyint(a0/a1);

#if defined(BOOST_SIMD_NO_INVALIDS)
      A0  a2 = if_allbits_else(is_eqz(a1),  fma(-d, a1, a0));
#else
      A0  a2 = if_allbits_else(logical_or(is_invalid(a0), is_eqz(a1)),  fma(-d, a1, a0));
#endif
      return {a2, toint(d)};
    }
  };
} } }


#endif
