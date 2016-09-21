//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ERFC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ERFC_HPP_INCLUDED

#include <boost/simd/arch/common/detail/generic/erf_kernel.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/zero.hpp>

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#endif
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( erfc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::double_<A0>, X>
                          )
  {
    A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      A0 x =  bs::abs(a0);
      A0 xx =  bs::sqr(x);
      A0 lim1 = A0(0.65);
      A0 lim2 = A0(2.2);
      auto test0 = bs::is_ltz(a0);
      auto test1 = bs::is_less(x, lim1);
      A0 r1 = bs::Zero<A0>();
      std::size_t nb = bs::nbtrue(test1);
      if(nb > 0)
      {
        r1 = bs::oneminus(x*detail::erf_kernel<A0>::erf1(xx));
        if (nb >= A0::static_size)
          return bs::if_else(test0, bs::Two<A0>()-r1, r1);
      }
      auto test2 = bs::is_less(x, lim2);
      auto test3 = bs::logical_andnot(test2, test1);
      A0 ex = bs::exp(-xx);

      std::size_t nb1 = bs::nbtrue(test3);
      if(nb1 > 0)
      {
        A0 z = ex*detail::erf_kernel<A0>::erfc2(x);
        r1 = bs::if_else(test1, r1, z);
        nb += nb1;
        if (nb >= A0::static_size)
          return bs::if_else(test0, Two<A0>()-r1, r1);
      }
      A0 z =  ex*detail::erf_kernel<A0>::erfc3(x);
      r1 = bs::if_else(test2, r1, z);
#ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( is_equal(x, Inf<A0>()), r1);
#endif
      return  bs::if_else(test0, bs::Two<A0>()-r1, r1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( erfc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      A0 x =  bs::abs(a0);
      auto test0 = bs::is_ltz(a0);
      A0 r1 = bs::Zero<A0>();
      auto test1 = bs::is_less(x, bs::Ratio<A0, 2, 3>());
      A0 z = x/inc(x);

      std::size_t nb = bs::nbtrue(test1);
      if(nb > 0)
      {
        r1 = detail::erf_kernel<A0>::erfc3(z);
        if (nb >= A0::static_size)
          return bs::if_else(test0, bs::Two<A0>()-r1, r1);
      }
      z -= A0(0.4);
      A0 r2 = exp(-sqr(x))*detail::erf_kernel<A0>::erfc2(z);
      r1 = if_else(test1, r1, r2);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( is_equal(x, Inf<A0>()), r1);
      #endif
      return bs::if_else(test0, bs::Two<A0>()-r1, r1);
    }
  };

} } }


#endif
