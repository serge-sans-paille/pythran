//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GENMASK_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/constant/allbits.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // genmask from logical
  BOOST_DISPATCH_OVERLOAD_IF( genmask_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_< bs::logical_<A0>, X >
                            )
  {
    using result_t = as_arithmetic_t<A0>;

    BOOST_FORCEINLINE result_t operator()( A0 const& a0 ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename is_bitwise_logical<A0>::type{});
    }

    BOOST_FORCEINLINE result_t do_( A0 const& a0, tt::true_type const& ) const BOOST_NOEXCEPT
    {
      return bitwise_cast<result_t>(a0);
    }

    BOOST_FORCEINLINE result_t do_( A0 const& a0, tt::false_type const& ) const BOOST_NOEXCEPT
    {
      return if_else(a0, Allbits<result_t>(), result_t(0));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( genmask_
                            , (typename A0,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
       return if_else(a0,  Allbits<A0>(), A0(0));
    }
  };
} } }

#endif
