//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SQRT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/touint.hpp>
#include <boost/simd/constant/four.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/assert_utils.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
       return _mm_sqrt_pd(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      using uint_type = bd::as_integer_t<A0,unsigned>;
      return simd::bitwise_cast<A0>(sqrt( simd::bitwise_cast<uint_type>(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return bs::toint(bs::sqrt(bs::tofloat(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      A0 n   = plus(shift_right(a0, 4), Four<A0>());
      A0 n1  = shift_right(n+a0/n, 1);

      auto ok = is_less(n1, n);
      n  = if_else(ok, n1, n);
      n1 = if_else(ok, shift_right(n+a0/n, 1), n1);

      ok = is_less(n1, n);
      n  = if_else(ok, n1, n);
      n  = if_dec( is_greater(n*n,a0), n);
      return n;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      auto na = is_nez(a0);
      A0 const  z1 = plus(shift_right(a0, 6), Ratio<A0, 16>());
      A0 const  z2 = plus(shift_right(a0,10), Ratio<A0, 256>());
      A0 const  C1 = Ratio<A0, 31679>();
      // choose a proper starting point for approximation
      A0 n  = if_else(is_less(a0, C1), z1, z2);
      auto ok =  is_gtz(n);
      n  = if_else(ok, n, One<A0>());

      A0 n1 = if_else(ok, shift_right(n+a0/n, 1), One<A0>());

      ok = is_less(n1, n);
      n  = if_else(ok, n1, n);
      n1 = if_else(ok, shift_right(n+a0/n, 1), n1);

      ok = is_less(n1, n);
      n  = if_else(ok, n1, n);
      n1 = if_else(ok, shift_right(n+a0/n, 1), n1);

      ok =  is_less(n1, n);
      n  = if_else(ok, n1, n);
      n  = if_dec( is_greater(n*n,a0), n);

     return if_plus(na, Zero<A0>(), n);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      auto na = is_nez(a0);
      A0 const z1 = plus(shift_right(a0, 6),    Ratio<A0,16>());
      A0 const z2 = plus(shift_right(a0,10),   Ratio<A0,256>());
      A0 const z3 = plus(shift_right(a0,13),  Ratio<A0,2048>());
      A0 const z4 = plus(shift_right(a0,16), Ratio<A0,16384>());
      A0 n  = if_else( is_greater(a0, Ratio<A0,177155824>())
                  , z4
                  , if_else( is_greater(a0, Ratio<A0,4084387>())
                        , z3
                        , if_else( is_greater(a0, Ratio<A0,31679>())
                                , z2
                                , z1
                                )
                        )
                  );
      auto ok =  is_gtz(n);
      n = if_else(ok, n, One<A0>());
      A0 n1 = if_else(ok, shift_right(n+a0/n, 1), One<A0>());

      ok = is_less(n1, n);
      n  = if_else(ok, n1, n);
      n1 = if_else(ok, shift_right(n+a0/n, 1), n1);

      ok =  is_less(n1, n);
      n  = if_else(ok, n1, n);
      n1 = if_else(ok, shift_right(n+a0/n, 1), n1);

      ok =  is_less(n1, n);
      n  = if_else(ok, n1, n);

      A0 tmp = minus(n*minus(n, One<A0>()), One<A0>());
      n  = if_dec( is_greater_equal(tmp+n,a0), n);
      n =  if_plus(na, Zero<A0>(), n);

      return n;
     }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint64_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return bs::touint(bs::sqrt(bs::tofloat(a0)));
    }
  };
} } }

#endif
