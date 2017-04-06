//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_SLIDE_HPP_INCLUDED

#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  namespace tt = nsm::type_traits;

  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename T, typename Offset)
                          , bs::ssse3_
                          , bs::pack_< bd::fundamental_<T>, bs::sse_ >
                          , bs::pack_< bd::fundamental_<T>, bs::sse_ >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T const& a0, T const& a1, Offset const&) const BOOST_NOEXCEPT
    {
      // Work on byte level
      using byte_t = typename T::template retype<std::uint8_t,16>;

      // Compute relative offsets
      using bitcount = tt::integral_constant < std::size_t
                                              , sizeof(as_arithmetic_t<typename T::value_type>)
                                              * Offset::value
                                              >;

      // Shift everything in place
      return bitwise_cast<T>( byte_t(_mm_alignr_epi8 ( bitwise_cast<byte_t>(a1), bitwise_cast<byte_t>(a0)
                                              , bitcount::value
                                              )
                                    )
                            );
    }
  };
} } }

#endif
