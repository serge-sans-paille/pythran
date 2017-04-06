//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NTHROOT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NTHROOT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_even.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/pow.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/exp.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( nthroot_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::integer_<A1>, X>
                          )
   {
      A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
      using bA0 = bs::as_logical_t<A0>;
      A0 x =  bs::abs(a0);
      A0 aa1 = bs::tofloat(a1);
      A0 y = bs::raw_(bs::pow_abs)(x,rec(aa1));
      bA0 nul_a1 =  bs::is_eqz(bitwise_cast<A0>(a1));
      bA0 is_ltza0 = is_ltz(a0);
      auto is_odda1 = is_odd(a1);
      A0 p = raw_(bs::pow_abs)(y, aa1);
      y = bs::if_plus( bs::logical_or(bs::is_nez(y), nul_a1)
                     , y
                     , -(p - x)/(aa1*p/y)
                     );
      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      bA0 test =  logical_andnot(is_ltza0, is_odda1);
      bA0 done =  test;
      y = if_nan_else(test, y);  // a0 < O and a1 is not odd
      bA0 newtest =  is_equal(x, One<A0>());
      test  = logical_andnot(newtest, done);
      done  = logical_or(done, newtest);
      y = if_else(test, a0, y); // 1^a1 or (-1)^a1
      newtest =  nul_a1;
      test  = logical_andnot(newtest, done);
      done  = logical_or(done, newtest);
      y =  if_else(test,
                   if_zero_else(is_less(x, One<A0>()),
                                sign(a0)*Inf<A0>()
                               ),
                   y);
      newtest =  is_eqz(a0);
      test  = logical_andnot(newtest, done);
      done  = logical_or(done, newtest);
      y =  if_zero_else(test, y);
      #ifndef BOOST_SIMD_NO_INFINITIES
      newtest =  is_inf(a0);
      test  = logical_andnot(newtest, done);
      done  = logical_or(done, newtest);
      y =  if_else(test, if_else(is_nez(a1), a0, One<A0>()), y);
      #endif
      return bs::bitwise_or(y, bs::bitofsign(a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD( nthroot_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::raw_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::integer_<A1>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(const raw_tag &, const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
     {
       auto aa1 =  abs(a1);
       A0 aa0 = abs(a0);
       A0 y = sign(a0)*bs::exp(bs::log(aa0)/tofloat(aa1));
       auto l =  is_ltz(aa1);
       y =  if_nan_else(logical_and(l, is_even(a1)), y);
       return if_else(is_ltz(a1), rec(y), y);
     }
   };


} } }

#endif
