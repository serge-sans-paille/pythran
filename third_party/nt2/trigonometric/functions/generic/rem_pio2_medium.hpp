//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_REM_PIO2_MEDIUM_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_REM_PIO2_MEDIUM_HPP_INCLUDED

#include <nt2/trigonometric/functions/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/pio2_1.hpp>
#include <nt2/include/constants/pio2_1t.hpp>
#include <nt2/include/constants/pio2_2.hpp>
#include <nt2/include/constants/pio2_2t.hpp>
#include <nt2/include/constants/pio2_3.hpp>
#include <nt2/include/constants/pio2_3t.hpp>
#include <nt2/include/constants/invpio_2.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/bitwise_and.hpp>
#include <nt2/include/functions/simd/minus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_medium_, tag::cpu_,
                             (A0)(A1),
                             (generic_ < floating_<A0> > )
                             (generic_ < integer_<A1>  > )
                             (generic_ < floating_<A0> > )
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& x, A1 & n, A0 & xr)
    {
      n = nt2::rem_pio2_medium(x, xr);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_medium_, tag::cpu_,
                             (A0),
                             (generic_ < floating_<A0> > )
                             )
  {
    typedef typename nt2::meta::as_integer<A0>::type int_t;
    typedef std::pair<int_t, A0>               result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 second;
      int_t const first = nt2::rem_pio2_medium(a0,second);
      return result_type(first, second);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_medium_, tag::cpu_,
                             (A0),
                             (generic_ < floating_<A0> > )
                             (generic_ < floating_<A0> > )
                             )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& t, A0 & xr) const
    {
      const A0 fn = nt2::round2even(t*Invpio_2<A0>());
      A0 r  = t-fn*nt2::Pio2_1<A0>();
      A0 w  = fn*nt2::Pio2_1t<A0>();
      A0 t2 = r;
      w  = fn*nt2::Pio2_2<A0>();
      r  = t2-w;
      w  = fn*nt2::Pio2_2t<A0>()-((t2-r)-w);
      t2 = r;
      w  = fn*nt2::Pio2_3<A0>();
      r  = t2-w;
      w  = fn*nt2::Pio2_3t<A0>()-((t2-r)-w);
      xr = r-w;
      return  bitwise_and(toint(fn), Three<result_type>());
    }
  };
} }
#endif
