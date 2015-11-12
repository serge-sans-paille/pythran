//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_PIO2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_REM_PIO2_HPP_INCLUDED

#include <nt2/trigonometric/functions/rem_pio2.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/aligned_load.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>

namespace nt2 { namespace ext
{


  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::rem_pio2_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0,A0 & xr,A0 & xc) const
    {
      typedef typename meta::scalar_of<A0>::type          stype;
      typedef typename meta::scalar_of<result_type>::type itype;
      static const nt2::uint32_t size = meta::cardinal_of<result_type>::value;
      BOOST_SIMD_ALIGNED_TYPE(itype) tmp[size];
      BOOST_SIMD_ALIGNED_TYPE(stype) txr[size];
      BOOST_SIMD_ALIGNED_TYPE(stype) txc[size];
      for(nt2::uint32_t i=0; i!=size; ++i)
      {
        // This prevent the may_alias ICE
        stype a = a0[i], r = txr[i], c = txc[i];
        tmp[i] =  nt2::rem_pio2(a, r, c);
        txr[i] = r;
        txc[i] = c;
      }

      xr = aligned_load<A0>(&txr[0], 0);
      xc = aligned_load<A0>(&txc[0], 0);
      return aligned_load<result_type>(&tmp[0], 0);
    }
  };

} }
#endif
