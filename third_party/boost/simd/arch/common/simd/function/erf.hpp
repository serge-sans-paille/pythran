//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ERF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ERF_HPP_INCLUDED

#include <boost/simd/arch/common/detail/generic/erf_kernel.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/six.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/if_neg.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/function/sign.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_nan.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/function/is_inf.hpp>
#endif
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( erf_
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
      auto test1 = bs::is_less(x, lim1);
      A0 r1 = bs::Zero<A0>();
      std::size_t nb = bs::nbtrue(test1);

      if(nb > 0)
      {
        r1 = a0*detail::erf_kernel<A0>::erf1(xx);
        if(nb >= A0::static_size) return r1;
      }
      auto test2 = bs::is_less(x, lim2);
      auto test3 = bs::logical_andnot(test2, test1);

      std::size_t nb1 = bs::nbtrue(test3);
      A0 ex = bs::exp(-xx);
      if(nb1 > 0)
      {
        A0 z = oneminus(ex*detail::erf_kernel<A0>::erfc2(x));
        A0 r2 = bs::if_neg(is_ltz(a0), z);
        r1 = bs::if_else(test1, r1, r2);
        nb += nb1;
        if(nb >= A0::static_size) return r1;
      }
      A0 z = bs::if_neg( bs::is_ltz(a0)
                       , bs::oneminus(ex*detail::erf_kernel<A0>::erfc3(x))
                       );
      #ifndef BOOST_SIMD_NO_INFINITIES
      z = bs::if_else(bs::is_inf(a0), bs::sign(a0), z);
      #endif
      return bs::if_else(test2, r1, z);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( erf_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    //Exhaustive test for: boost::dispatch::functor<boost::simd::tag::erf_, boost::simd::sse4_2_>
    //             versus: raw_erf
    //             With T: boost::simd::pack<float, 4ul, boost::simd::sse_>
    //           in range: [-88.3763, 88.3763]
    //         # of tests: 2237759818

    //2237759812/2237759818 values computed.
    // 877224467 values (39.20%)  within 0.0 ULPs
    //1359698419 values (60.76%)  within 0.5 ULPs in range [-3.780924320e+00, 3.780924320e+00]. Example: -3.780924320e+00 returns -9.999999404e-01 instead of -9.999998808e-01
    //    627698 values (0.03%) within 1.0 ULPs in range [-5.208772127e-39, 5.208772127e-39]. Example: -5.208772127e-39 returns -5.877468952e-39 instead of -5.877470353e-39
    //    156912 values (0.01%) within 2.0 ULPs in range [-2.604377656e-39, 2.604377656e-39]. Example: -2.604377656e-39 returns -2.938724667e-39 instead of -2.938726068e-39
    //     39234 values (0.00%) within 4.0 ULPs in range [-1.302191630e-39, 1.302191630e-39]. Example: -1.302191630e-39 returns -1.469365136e-39 instead of -1.469366537e-39
    //      9808 values (0.00%) within 8.0 ULPs in range [-6.510600821e-40, 6.510600821e-40]. Example: -6.510600821e-40 returns -7.346419303e-40 instead of -7.346433316e-40
    //      2452 values (0.00%) within 16.0 ULPs  in range [-3.255328437e-40, 3.255328437e-40]. Example: -3.255328437e-40 returns -3.673237678e-40 instead of -3.673251691e-40
    //       618 values (0.00%) within 32.0 ULPs  in range [-1.626108777e-40, 1.626108777e-40]. Example: -1.626108777e-40 returns -1.834860209e-40 instead of -1.834874222e-40
    //       144 values (0.00%) within 64.0 ULPs  in range [-7.796264136e-41, 7.796264136e-41]. Example: -7.796264136e-41 returns -8.797071499e-41 instead of -8.797211629e-41
    //        50 values (0.00%) within 128.0 ULPs in range [-3.892947264e-41, 3.892947264e-41]. Example: -3.892947264e-41 returns -4.392650296e-41 instead of -4.392790426e-41
    //        10 values (0.00%) within 256.0 ULPs in range [-1.290736015e-41, 1.290736015e-41]. Example: -1.290736015e-41 returns -1.456369494e-41 instead of -1.456509624e-41
    A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      A0 x =  bs::abs(a0);
      A0 r1 = bs::Zero<A0>();
      auto test1 = bs::is_less(x, Ratio<A0, 2, 3>());
      std::size_t nb = bs::nbtrue(test1);
      if(nb > 0)
      {
        r1 =  a0*detail::erf_kernel<A0>::erf1(sqr(x));
        if(nb >= A0::static_size)
          return r1;
      }
      A0 z = x/inc(x);
      z-= A0(0.4);
      A0 r2 =   oneminus(exp(-sqr(x))*detail::erf_kernel<A0>::erfc2(z));
      r2 = bs::if_neg(is_ltz(a0), r2);
      r1 = if_else(test1, r1, r2);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = bs::if_else(bs::is_inf(a0), bs::sign(a0), r1);
      #endif
      return r1;
    }
  };

} } }


#endif
