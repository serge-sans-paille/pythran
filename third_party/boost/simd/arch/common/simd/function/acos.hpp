//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ACOS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ACOS_HPP_INCLUDED

#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/arch/common/detail/simd/f_invtrig.hpp>
#include <boost/simd/arch/common/detail/simd/d_invtrig.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF ( acos_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {

    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &,  A0 const& a0) const BOOST_NOEXCEPT
    {
      //Exhaustive test for: boost::simd::detail::decorated_functor<boost::simd::tag::acos_, boost::simd::sse4_2_, boost::simd::pedantic_tag>
      //             versus: raw_acos
      //             With T: boost::simd::pack<float, 4ul, boost::simd::sse_>
      //           in range: [-1, 1]
      //         # of tests: 2130706432

      //2130706432/2130706432 values computed.
      //1968259973 values (92.38%)  within 0.0 ULPs
      // 162446459 values (7.62%) within 0.5 ULPs in range [-9.999999404e-01, 9.999996424e-01]. Example: -9.999999404e-01 returns 3.141247511e+00 instead of 1.570796251e+00
      return detail::invtrig_base<A0,tag::radian_tag,tag::simd_type>::acos(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( acos_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {

    BOOST_FORCEINLINE A0 operator() (A0 const& a0) const BOOST_NOEXCEPT
    {
      //Exhaustive test for: boost::dispatch::functor<boost::simd::tag::acos_, boost::simd::sse4_2_>
      //             versus: raw_acos
      //             With T: boost::simd::pack<float, 4ul, boost::simd::sse_>
      //           in range: [-1, 1]
      //         # of tests: 2130706432

      //2130706432/2130706432 values computed.
      // 1967049938 values (92.32%) within 0.0 ULPs
      //  163364747 values (99.99%) within 0.5 ULPs in range [-9.999999404e-01, 9.999991655e-01]. Example: -9.999999404e-01 returns 3.141247511e+00 instead of 3.141247272e+00
      //     252025 values (100.00%)  within 1.0 ULPs in range [8.775838017e-01, 9.999970198e-01]. Example: 8.775838017e-01 returns 4.999974966e-01 instead of 4.999974072e-01
      //      32464 values (100.00%)  within 2.0 ULPs in range [9.922016263e-01, 9.999964833e-01]. Example: 9.922016263e-01 returns 1.249682903e-01 instead of 1.249682382e-01
      //       5800 values (100.00%)  within 4.0 ULPs in range [9.980521798e-01, 9.999993443e-01]. Example: 9.980521798e-01 returns 6.242525578e-02 instead of 6.242519990e-02
      //       1148 values (100.00%)  within 8.0 ULPs in range [9.995126724e-01, 9.999985695e-01]. Example: 9.995126724e-01 returns 3.122079372e-02 instead of 3.122073598e-02
      //        238 values (100.00%)  within 16.0 ULPs  in range [9.998818040e-01, 9.999994636e-01]. Example: 9.998818040e-01 returns 1.537525654e-02 instead of 1.537519693e-02
      //         58 values (100.00%)  within 32.0 ULPs  in range [9.999715686e-01, 9.999995828e-01]. Example: 9.999715686e-01 returns 7.540822029e-03 instead of 7.540762424e-03
      //          9 values (100.00%)  within 64.0 ULPs  in range [9.999928474e-01, 9.999991059e-01]. Example: 9.999928474e-01 returns 3.782153130e-03 instead of 3.782212501e-03
      //          4 values (100.00%)  within 128.0 ULPs in range [9.999996424e-01, 9.999998212e-01]. Example: 9.999996424e-01 returns 8.456707001e-04 instead of 8.457279764e-04
      //          1 values (100.00%)  within 256.0 ULPs in range [9.999999404e-01, 9.999999404e-01]. Example: 9.999999404e-01 returns 3.452301025e-04 instead of 3.452669771e-04
      return Pio_2<A0>()-detail::invtrig_base<A0,tag::radian_tag,tag::simd_type>::asin(a0);
    }
  };

} } }

#endif
