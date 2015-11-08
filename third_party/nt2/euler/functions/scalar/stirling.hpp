//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_STIRLING_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_STIRLING_HPP_INCLUDED

#include <nt2/euler/functions/stirling.hpp>
#include <nt2/euler/functions/details/stirling_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2pi.hpp>
#include <nt2/include/constants/stirlinglargelim.hpp>
#include <nt2/include/constants/stirlingsplitlim.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/rec.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stirling_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      if (nt2::is_nan(a0)) return a0;
      #endif
      if (a0 > nt2::Stirlinglargelim<A0>()) return nt2::Inf<A0>();
      A0 w = nt2::rec(a0);
      w = fma(w,details::stirling_kernel<A0>::stirling1(w), nt2::One<A0>());
      A0 y = nt2::exp(-a0);
      if(nt2::is_eqz(y)) return nt2::Inf<A0>();
      A0 z =  a0 - nt2::Half<A0>();
      if( a0 >= nt2::Stirlingsplitlim<A0>() )
      { /* Avoid overflow in pow() */
        const A0 v = nt2::pow(a0,z*Half<A0>());
        y *= v;
        y *= v;
      }
      else
      {
        y *= nt2::pow( a0, z );
      }
      y *= nt2::Sqrt_2pi<A0>()*w;
      return y;
    }
  };
} }

#endif
