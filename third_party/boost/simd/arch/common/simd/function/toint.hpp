//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TOINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/modf.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(toint_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::uint_<A0>, X>
                          )
   {
      using result = bd::as_integer_t<A0, signed> ;
      BOOST_FORCEINLINE result operator()(A0 const& a0) const
      {
        return bitwise_cast<result>(a0);
      }
   };

   BOOST_DISPATCH_OVERLOAD(toint_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::int_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(A0 const& a0) const
     {
        return a0;
     }
   };

  BOOST_DISPATCH_OVERLOAD_IF(toint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pedantic_tag
                            , bs::pack_<bd::double_<A0>, X>
                          )
   {
     using result = bd::as_integer_t<A0, signed> ;
     BOOST_FORCEINLINE result operator()(pedantic_tag const &
                                        , A0 const& a0) const
     {
       const int32_t Vim32 = Valmin<int32_t>();
       const result Vim =  result(Vim32);
       const result Vax = -result(Vim32);
       constexpr int S = 32;
       A0 z = ldexp(a0, -S);
       A0 t1, t2;
       std::tie(t1, t2) =  modf(z);
       t1 = ldexp(t1, S); // abs(t1) < 2^32
       result z1 = toint(t1)+ ldexp(toint(t2), S);
       return if_else(logical_and(z1 == Vim, is_gtz(a0)), Vax, z1);
     }
   };

   BOOST_DISPATCH_OVERLOAD(toint_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::single_<A0>, X>
                          )
   {
     using result = bd::as_integer_t<A0, signed> ;
     BOOST_FORCEINLINE result operator()(pedantic_tag const &
                                        , A0 const& a0) const
     {
       return toint(a0);
     }
   };

} } }

#include <boost/simd/arch/common/simd/function/toint_s.hpp>

#endif

