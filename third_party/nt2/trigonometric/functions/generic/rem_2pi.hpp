//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_REM_2PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_REM_2PI_HPP_INCLUDED

#include <nt2/trigonometric/functions/rem_2pi.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/threeeps.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/inv2pi.hpp>
#include <nt2/include/constants/pix2_1.hpp>
#include <nt2/include/constants/pix2_2.hpp>
#include <nt2/include/constants/pix2_3.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>

namespace nt2 { namespace ext
{


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, tag::cpu_,
                             (A0),
                             (generic_ < floating_<A0> > )
    )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0) const
    {
      typedef typename nt2::meta::as_integer<A0>::type iA0;
      A0 xr;
      iA0 n = nt2::rem_pio2(a0, xr);
      xr = xr+nt2::tofloat(n)*nt2::Pio_2<A0>();
      return if_else(gt(xr, nt2::Pi<A0>()), xr-nt2::Twopi<A0>(), xr);
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_2pi_, tag::cpu_,
                             (A0)(A1),
                             (generic_ <floating_<A0> > )
                             (target_ <unspecified_<A1> >)
    )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef typename A1::type selector;
      return rem2pi<selector, void>::rem(a0);
    }
  private:
    template < class T, class dummy = void> struct rem2pi
    {
      static inline result_type rem(A0 const&, A0 &, A0&)
      {
        BOOST_ASSERT_MSG(false, "wrong target for rem_2pi");
      }
    };
    template < class dummy> struct rem2pi < big_, dummy>
    {
      static inline result_type rem(A0 const& x)
      {
        return nt2::rem_2pi(x);
      }
    };
    template < class dummy> struct rem2pi < very_small_, dummy > // |a0| <2*pi
    {
      static inline result_type rem(A0 const& x)
      {
        return nt2::if_else(nt2::gt(x, nt2::Pi<A0>()), x-nt2::Twopi<A0>(),
                     nt2::if_else(lt(x, -nt2::Pi<A0>()), x+nt2::Twopi<A0>(), x));
      }
    };
    template < class dummy> struct rem2pi < small_, dummy >// |a0| <= 20*pi
    {
      static inline result_type rem(A0 const& x)
      {
        A0 xi =  nt2::round2even(x*nt2::Inv2pi<A0>());
        A0 xr = x-xi*nt2::Pix2_1<A0>();
        xr -= xi*nt2::Pix2_2<A0>();
        xr -= xi*nt2::Pix2_3<A0>();
        return xr;
      }
    };

    template < class dummy> struct rem2pi < medium_, dummy >
    {
      static inline result_type rem(A0 const& x)
      {
        A0 xr;
        typedef typename nt2::meta::as_integer<A0>::type iA0;
        iA0 n = rem_pio2_medium(x, xr);
        xr += nt2::tofloat(n)*Pio_2<A0>();
        xr = if_else(gt(xr, Pi<A0>()), xr-Twopi<A0>(), xr);
        return xr;
      }
    };
  };
} }
#endif
