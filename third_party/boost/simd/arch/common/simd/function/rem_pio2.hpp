//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REM_PIO2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REM_PIO2_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/aligned_load.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <tuple>
#include <utility>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD( rem_pio2_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      using iA0 =  bd::as_integer_t<A0>;
      using result = std::pair<A0,A0>;
      inline result operator()(A0 const& a0) const
      {
        using stype =  bd::scalar_of_t<A0>;
        static const uint32_t size = bs::cardinal_of<A0>::value;
        alignas(iA0) std::array<stype, size> tmp;
        alignas( A0) std::array<stype , size> txr;
        for(uint32_t i=0; i!=size; ++i)
        {
          std::tie(tmp[i],txr[i]) =  bs::rem_pio2(a0[i]);
        }
        return result(aligned_load<A0>(&tmp[0], 0), aligned_load<A0>(&txr[0], 0));
      }
   };

} } }

#endif
