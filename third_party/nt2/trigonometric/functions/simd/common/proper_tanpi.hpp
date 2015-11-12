//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_PROPER_TANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_PROPER_TANPI_HPP_INCLUDED

#include <nt2/trigonometric/functions/proper_tanpi.hpp>
#include <nt2/trigonometric/functions/simd/common/impl/trigo.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_not_less_equal.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proper_tanpi_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 absa0 = nt2::abs(a0);
      bA0 test = nt2::le(absa0,  Quarter<A0>());
      A0 a = nt2::if_else(test, absa0, nt2::Half<A0>()-absa0);
      A0 that = details::trig_base<A0,pi_tag,tag::simd_type, clipped_pio4_>::tana(a);
      that = nt2::negif(nt2::is_ltz(a0), that);
      return nt2::if_nan_else(boost::simd::is_nle(absa0, nt2::Half<A0>()),
                              nt2::if_else(test, that, rec(that)));
    }
  };
} }

#endif
