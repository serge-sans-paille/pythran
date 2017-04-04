//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ACOS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ACOS_HPP_INCLUDED

#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/arch/common/detail/scalar/f_invtrig.hpp>
#include <boost/simd/arch/common/detail/scalar/d_invtrig.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( acos_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      return detail::invtrig_base<A0,tag::radian_tag,tag::not_simd_type>::acos(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( acos_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      //Exhaustive test for: boost::dispatch::functor<boost::simd::tag::acos_, boost::simd::sse4_2_>
      //             versus: raw_acos
      //             With T: boost::simd::pack<float, 4ul, boost::simd::sse_>
      //           in range: [-1, 1]
      //         # of tests: 2130706432

      //2130706432/2130706432 values computed.
      //1963801827 values (92.17%)  within 0.0 ULPs
      // 166345266 values (7.81%) within 0.5 ULPs in range [-9.999999404e-01, 9.999821186e-01]. Example: -9.999999404e-01 returns 3.141247511e+00 instead of 3.141247272e+00
      //    464988 values (0.02%) within 1.0 ULPs in range [8.414715528e-01, 9.999965429e-01]. Example: 8.414715528e-01 returns 5.707951188e-01 instead of 5.707952976e-01
      //     78131 values (0.00%) within 2.0 ULPs in range [9.689134359e-01, 9.999967217e-01]. Example: 9.689134359e-01 returns 2.499957830e-01 instead of 2.499959022e-01
      //     12485 values (0.00%) within 4.0 ULPs in range [9.922192097e-01, 9.999997616e-01]. Example: 9.922192097e-01 returns 1.248269826e-01 instead of 1.248270944e-01
      //      2792 values (0.00%) within 8.0 ULPs in range [9.995127916e-01, 9.999988079e-01]. Example: 9.995127916e-01 returns 3.121681698e-02 instead of 3.121691570e-02
      //       717 values (0.00%) within 16.0 ULPs  in range [9.998779893e-01, 9.999988675e-01]. Example: 9.998779893e-01 returns 1.562126074e-02 instead of 1.562134363e-02
      //       175 values (0.00%) within 32.0 ULPs  in range [9.999695420e-01, 9.999998212e-01]. Example: 9.999695420e-01 returns 7.804826833e-03 instead of 7.804886904e-03
      //        42 values (0.00%) within 64.0 ULPs  in range [9.999927878e-01, 9.999995232e-01]. Example: 9.999927878e-01 returns 3.797844984e-03 instead of 3.797939047e-03
      //         6 values (0.00%) within 128.0 ULPs in range [9.999984503e-01, 9.999998808e-01]. Example: 9.999984503e-01 returns 1.760439132e-03 instead of 1.760523301e-03
      //         2 values (0.00%) within 256.0 ULPs in range [9.999996424e-01, 9.999997020e-01]. Example: 9.999996424e-01 returns 8.456269861e-04 instead of 8.457279764e-04
      //         1 values (0.00%) within 512.0 ULPs in range [9.999999404e-01, 9.999999404e-01]. Example: 9.999999404e-01 returns 3.451863886e-04 instead of 3.452669771e-04
      A0 z = Pio_2<A0>()-detail::invtrig_base<A0,tag::radian_tag,tag::not_simd_type>::asin(a0);
      return z+Pio_2lo<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( acos_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::acos(a0);
    }
  };
} } }

#endif
