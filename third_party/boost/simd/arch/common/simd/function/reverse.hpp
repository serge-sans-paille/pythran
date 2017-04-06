//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REVERSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/extract.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( reverse_
                            , (typename A0, typename X)
                            , (bs::is_bitwise_logical<A0>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return bitwise_cast<A0>(reverse( bitwise_cast<as_arithmetic_t<A0>>(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( reverse_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return do_(a0, typename A0::traits::storage_kind{}, typename A0::traits::element_range{});
    }

    template<typename K, typename... N>
    BOOST_FORCEINLINE A0 do_(const A0& a0, K const&, nsm::list<N...> const&) const BOOST_NOEXCEPT
    {
      return A0( extract<A0::static_size-N::value-1>(a0)... );
    }

    template<typename... N> BOOST_FORCEINLINE
    A0 do_(const A0& a0, aggregate_storage const&, nsm::list<N...> const&) const BOOST_NOEXCEPT
    {
      // reverse each half and permute them
      return {{ {reverse(a0.storage()[1]), reverse(a0.storage()[0])} }};
    }
  };
} } }

#endif
