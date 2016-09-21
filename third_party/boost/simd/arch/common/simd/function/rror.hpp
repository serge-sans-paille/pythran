//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_RROR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_RROR_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/rol.hpp>
#include <boost/simd/function/ror.hpp>
#include <boost/simd/function/unary_minus.hpp>
#ifndef NDEBUG
#include <boost/simd/function/max.hpp>
#include <boost/simd/constant/zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF(rror_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::arithmetic_<A0>, X>
                             , bs::pack_<bd::int_<A1>, X>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        #ifndef NDEBUG
        return bitwise_cast<A0>( if_else ( is_gtz(a1)
                                                  , ror ( bitwise_cast<A1>(a0)
                                                        , max(Zero<A1>(),a1)
                                                        )
                                                  , rol ( bitwise_cast<A1>(a0)
                                                        , max(Zero<A1>(),-a1)
                                                        )
                                                  )
                                        );
        #else
        return bitwise_cast<A0>( if_else ( is_gtz(a1)
                                                  , ror(bitwise_cast<A1>(a0), a1)
                                                  , rol(bitwise_cast<A1>(a0),-a1)
                                                  )
                                        );
        #endif
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(rror_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::arithmetic_<A0>, X>
                             , bs::pack_<bd::uint_<A1>, X>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        return bitwise_cast<A0>( ror( bitwise_cast<A1>(a0), a1 ) );
      }
   };
} } }

#endif
