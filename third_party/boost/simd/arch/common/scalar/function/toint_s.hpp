//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TOINT_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TOINT_S_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/is_nan.hpp>
#endif
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/saturate.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( toint_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    using result_t = A0;

    BOOST_FORCEINLINE result_t operator() (const saturated_tag &,  A0 a0
                                    ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( toint_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::uint_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;

    BOOST_FORCEINLINE result_t operator() (const saturated_tag &,  A0 a0
                                    ) const BOOST_NOEXCEPT
    {
      return result_t(saturate<result_t>(a0));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( toint_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;

    BOOST_FORCEINLINE result_t operator() (const saturated_tag &,  A0 a0
                                    ) const BOOST_NOEXCEPT
    {
    #ifndef BOOST_SIMD_NO_NANS
      if (simd::is_nan(a0)) return Zero<result_t>();
    #endif
      if (a0 >= Valmax<result_t>()) return Valmax<result_t>();
      if (a0 <= Valmin<result_t>()) return Valmin<result_t>();
      return result_t(a0);
    }
  };
} } }


#endif
