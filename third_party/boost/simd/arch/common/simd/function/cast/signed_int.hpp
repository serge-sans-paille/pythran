//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_SIGNED_INT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_SIGNED_INT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace ext
{
 namespace bd = boost::dispatch;
 namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1, typename X, std::size_t Size)
                          , bd::cpu_
                          , bs::pack_< bd::ints_<A0,Size>, X>
                          , bd::target_< bd::scalar_< bd::ints_<A1,Size> > >
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename std::is_same<A0, result>::type{});
    }

    BOOST_FORCEINLINE result do_(A0 const& a0, std::false_type const& ) const BOOST_NOEXCEPT
    {
      return bitwise_cast<result>(a0);
    }

    BOOST_FORCEINLINE result do_(A0 const& a0, std::true_type const& ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
} } }

#endif
