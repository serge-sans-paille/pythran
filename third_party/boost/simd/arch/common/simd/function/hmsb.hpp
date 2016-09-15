//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <climits>
#include <cstddef>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(hmsb_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE std::size_t operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        using stype = bd::scalar_of_t<A0>;
        using itype = bd::as_integer_t<stype, unsigned>;
        std::size_t z = 0;
        const std::size_t N = A0::static_size;
        for(std::size_t i = 0; i != N; ++i)
        {
          stype t = a0[i]; // TO DO why must I use t or else bitwise_cast does not compile (clang 3.6)?
          z |= size_t((bitwise_cast<itype>(t) >> (sizeof(stype)*CHAR_BIT - 1)) << i);
        }
         return z;
      }
   };

   BOOST_DISPATCH_OVERLOAD(hmsb_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bs::logical_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE std::size_t operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return bs::hmsb(bs::genmask(a0));
      }
   };

} } }

#endif

