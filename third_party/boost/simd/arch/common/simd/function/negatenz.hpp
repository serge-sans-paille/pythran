//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEGATENZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEGATENZ_HPP_INCLUDED

#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/signnz.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD_IF ( negatenz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::signed_<A0>, X>
                          , bs::pack_<bd::signed_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      return multiplies(a0, signnz(a1));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( negatenz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( negatenz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      return bitwise_xor(bitofsign(a1), a0);
    }
  };
} } }


#endif
