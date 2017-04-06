//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_POW_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_POW_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/if_neg.hpp>
#include <boost/simd/function/pow_abs.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/sqr.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF( pow_
                           , (typename A0,typename X)
                           , (detail::is_native<X>)
                           , bd::cpu_
                           , bs::pack_<bd::floating_<A0>,X>
                           , bs::pack_<bd::floating_<A0>,X>
                           )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) BOOST_NOEXCEPT
    {
      auto nega0 = is_negative(a0);
      A0 z = pow_abs(a0, a1);
      z =  if_neg(logical_and(is_odd(a1), nega0), z);
      auto invalid =  logical_andnot(nega0, logical_or(is_flint(a1), is_inf(a1)));
      z = if_else(invalid, Nan<A0>(), z);
      return z;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(pow_
                          , (typename A0,typename A1,typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          , bs::pack_<bd::uint_<A1>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const A0& a0, const A1& a1 ) const BOOST_NOEXCEPT
      {
        A0 base = a0;
        A1 exp = a1;
        A0 result = One<A0>();
        while(bs::any(exp))
        {
          result *= if_else(is_odd(exp), base, One<A0>());
          exp =  exp >> 1;
          base = sqr(base);
        }
        return result;
       }
   };

  BOOST_DISPATCH_OVERLOAD_IF ( pow_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bd::constant_< bd::uint_<A1>>
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE result_type operator() ( A0 const& a0, A1) const BOOST_NOEXCEPT
    {
      return pow_expander<A1::value>::call(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( pow_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          , bd::constant_< bd::int_<A1>>
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE result_type operator() ( A0 const& a0, A1) const BOOST_NOEXCEPT
    {
      return eval(a0, boost::mpl::bool_<(A1::value >= 0)>());
    }

    BOOST_FORCEINLINE result_type eval( A0 const& a0, boost::mpl::true_) const BOOST_NOEXCEPT
    {
      return pow_expander<A1::value>::call(a0);
    }

    BOOST_FORCEINLINE result_type eval( A0 const& a0, boost::mpl::false_) const BOOST_NOEXCEPT
    {
      return pow_expander<-A1::value>::call(rec(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( pow_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bd::scalar_< bd::uint_<A1>>
                          )
  {
    using result_type = A0;

    A0 operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      A0 base = a0;
      A1 exp = a1;

      result_type result = One<result_type>();
      while(exp)
      {
        if(is_odd(exp))
          result *= base;
        exp >>= 1;
        base = sqr(base);
      }

      return result;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( pow_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::integer_<A0>, X>
                          , bs::pack_< bd::int_<A1>, X>
                          )
  {
    using result_type = A0;

    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::assert_all(a1 >= 0), "integral pow with signed exponent" );

      using u_t =  bd::as_integer_t<A1, unsigned>;
      return pow(a0, bitwise_cast<u_t>(a1));
    }
  };


  BOOST_DISPATCH_OVERLOAD_IF ( pow_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          , bs::pack_< bd::int_<A1>, X>
                          )
  {
    using result_type = A0;

    A0 operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      using u_t =  bd::as_integer_t<A1, unsigned>;
      auto ltza1 = is_ltz(a1);
      A0 p = pow(a0, bitwise_cast<u_t>(if_neg(ltza1, a1)));
      return if_else(ltza1, rec(p), p);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( pow_
                            , (typename A0,typename X)
                            , (detail::is_native<X>)
                            , bs::raw_tag
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>,X>
                            , bs::pack_<bd::floating_<A0>,X>
                           )
  {
    BOOST_FORCEINLINE A0 operator()(const raw_tag &,
                                    const A0& a0, const A0& a1) BOOST_NOEXCEPT
    {
      auto nega0 = is_negative(a0);
      A0 z = raw_(pow_abs(a0, a1));
      z =  if_neg(logical_and(is_odd(a1), nega0), z);
      auto invalid =  logical_andnot(nega0, logical_or(is_flint(a1), is_inf(a1)));
      z = if_else(invalid, Nan<A0>(), z);
      return z;
    }
  };
} } }

#endif
