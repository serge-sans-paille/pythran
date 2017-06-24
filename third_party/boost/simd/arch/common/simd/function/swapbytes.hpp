//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SWAPBYTES_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace tt = nsm::type_traits;

    template<std::size_t N> struct swap_bytes_helper
    {
      template<typename I, typename C>
      struct apply : tt::integral_constant < std::size_t, N*(I::value/N)+N-1-I::value%N>
      {};
    };
  }
} }

namespace boost { namespace simd { namespace ext
{

  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF(swapbytes_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integer_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      using s0        = typename A0::value_type;
      static const size_t N = A0::static_size*sizeof(s0);
      using i8        = pack<uint8_t, N>;
      using pattern_t = detail::swap_bytes_helper<sizeof(s0)>;

      return bitwise_cast<A0>(shuffle<pattern_t>(bitwise_cast<i8>(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD(swapbytes_
                         , (typename A0, typename X)
                         , bd::cpu_
                         , bs::pack_<bd::ints8_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

} } }

#endif

