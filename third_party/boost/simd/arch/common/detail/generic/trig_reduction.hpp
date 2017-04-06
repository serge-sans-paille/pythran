//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSbd:E_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_TRIG_REDUCTION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_TRIG_REDUCTION_HPP_INCLUDED

#include <boost/simd/function/rem_pio2_medium.hpp>
#include <boost/simd/function/rem_pio2_cephes.hpp>
#include <boost/simd/function/rem_pio2_straight.hpp>
#include <boost/simd/function/rem_pio2.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

#include <boost/simd/function/all.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/if_else_nan.hpp>
#include <boost/simd/function/is_not_greater.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/function/inrad.hpp>
#include <boost/simd/function/quadrant.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/constant/pio_4.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/detail/constant/medium_pi.hpp>
#include <boost/simd/constant/false.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/real.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <utility>

namespace boost { namespace simd
{
  namespace detail
  {
    template< class A0
            , class unit_tag
            , class style
            , class mode
            , class base_A0 = bd::scalar_of_t<A0>
    >
    struct trig_reduction;

    // This class exposes the public static member:
    // reduce:                to provide range reduction
    //
    // unit_tag allows to choose statically the scaling  among radian_tag, pi_tag, degree_tag
    // meaning that the cosa function will (for example) define respectively
    // x-->cos(x)          (radian_tag),
    // x-->cos(pi*x)        (pi_tag)
    // x-->cos((pi/180)*x) (degree_tag)
    //

    // trigonometric reduction strategies in the [-pi/4, pi/4] range.
    // these reductions are used in the accurate and fast
    // trigonometric functions with different policies


    template<class A0, class style, class mode>
    struct trig_reduction<A0,tag::degree_tag, style, mode>//always equivalent to  tag::big_tag>
    {

      static BOOST_FORCEINLINE auto cot_invalid(const A0& x) BOOST_NOEXCEPT
      -> decltype(is_nez(x)&&is_flint(x*Ratio<A0,1,180>()))
      {
        return is_nez(x)&&is_flint(x*Ratio<A0,1,180>());
      }
      static BOOST_FORCEINLINE auto tan_invalid(const A0& x) BOOST_NOEXCEPT
      -> decltype(is_flint((x- Ratio<A0,90>())*Ratio<A0,1,180>()))
      {
        return is_flint((x- Ratio<A0,90>())*Ratio<A0,1,180>());
      }

      static BOOST_FORCEINLINE A0 reduce(const A0& x, A0& xr) BOOST_NOEXCEPT
      {
        A0 xi = nearbyint(x*Ratio<A0,1,90>());
        A0 x2 = x - xi * Ratio<A0,90>();
        xr =  inrad(x2);
        return quadrant(xi);
      }
    };

#ifdef BOOST_SIMD_HAS_X87
    template<class A0, class mode>
    struct trig_reduction<A0, tag::degree_tag, tag::not_simd_type, mode> //always equivalent to  tag::big_tag>
    {

      static BOOST_FORCEINLINE auto cot_invalid(const A0& x) BOOST_NOEXCEPT
      -> decltype(is_nez(x)&&is_flint(x*Ratio<A0,1,180>()))
      {
        return is_nez(x)&&is_flint(x/Constant<A0,180>());
      }
      static BOOST_FORCEINLINE auto tan_invalid(const A0& x) BOOST_NOEXCEPT
      -> decltype(is_flint((x- Ratio<A0,90>())/Constant<A0,180>()))
      {
        return is_flint((x- Ratio<A0,90>())*Ratio<A0,1,180>());
      }

      static BOOST_FORCEINLINE A0 reduce(const A0& x, A0& xr) BOOST_NOEXCEPT
      {
        A0 xi = nearbyint(x*Ratio<A0,1,90>());
        A0 x2 = x - xi * Ratio<A0,90>();

        xr =  inrad(x2);
        return quadrant(xi);
      }
    };
#endif

    template < class A0, class style, class mode>
    struct trig_reduction < A0, tag::pi_tag,  style, mode> //always equivalent to tag::big_tag>
    {

      static BOOST_FORCEINLINE auto cot_invalid(const A0& x) BOOST_NOEXCEPT
      -> decltype(is_nez(x)&&is_flint(x))
      {
        return is_nez(x)&&is_flint(x);
      }
      static BOOST_FORCEINLINE auto tan_invalid(const A0& x) BOOST_NOEXCEPT
      -> decltype(is_flint(x-Half<A0>()))
      {
        return is_flint(x-Half<A0>()) ;
      }

      static BOOST_FORCEINLINE A0 reduce(const A0& x,  A0& xr) BOOST_NOEXCEPT
      {
        A0 xi = nearbyint(x*Two<A0>());
        A0 x2 = x - xi * Half<A0>();
        xr = x2*Pi<A0>();
        return quadrant(xi);
      }
    };
  }
} }


#endif
