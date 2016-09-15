//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MULTIPLIES_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MULTIPLIES_S_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/split_multiplies.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

/* No native groups for 64-bit SSE;
 * we use bit tricks instead of calling saturate. */

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::sse2_
                          , bs::saturated_tag
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const saturated_tag &
                                    , const A0 & a0
                                    , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using stype  = bd::scalar_of_t<A0>;
      using untype = bd::as_unsigned_t<A0>;
      using utype  = bd::upgrade_t<A0>;

      utype res0, res1;
      std::tie(res0, res1) = split_multiplies(a0, a1);

      untype res2 = shift_right(bitwise_cast<untype>(a0 ^ a1), sizeof(stype)*CHAR_BIT-1)
                  + static_cast<typename bd::scalar_of<untype>::type>(Valmax<stype>());

      A0 hi = group( shift_right(res0, sizeof(stype)*CHAR_BIT)
                   , shift_right(res1, sizeof(stype)*CHAR_BIT)
                   );
      A0 lo = group(res0, res1);

      return if_else( hi != shift_right(lo, sizeof(stype)*CHAR_BIT-1)
                    , bitwise_cast<A0>(res2)
                    , lo
                    );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::sse2_
                          , bs::saturated_tag
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const saturated_tag &
                                    ,  const A0 & a0
                                    , const A0 & a1
                                    ) const BOOST_NOEXCEPT
    {
      using stype  = bd::scalar_of_t<A0>;
      using utype  = bd::upgrade_t<A0>;

      utype res0, res1;
      std::tie(res0, res1) = split_multiplies(a0, a1);

      return group(res0, res1)
           | genmask( group( shift_right(res0, sizeof(stype)*CHAR_BIT)
                           , shift_right(res1, sizeof(stype)*CHAR_BIT)
                           )
                    );
    }
  };

} } }

#endif
