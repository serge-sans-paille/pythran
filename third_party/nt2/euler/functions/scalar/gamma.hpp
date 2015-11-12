//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_GAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_GAMMA_HPP_INCLUDED
#include <nt2/euler/functions/gamma.hpp>
#include <nt2/euler/functions/details/gamma_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_even.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/sinpi.hpp>
#include <nt2/include/functions/scalar/stirling.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if (is_eqz(a0)) return copysign(Inf<A0>(), a0);
      #ifndef BOOST_SIMD_NO_INVALIDS
      if( nt2::is_nan(a0) || (a0 == nt2::Minf<A0>()) ) return nt2::Nan<A0>();
      if (a0 == nt2::Inf<A0>()) return a0;
      #endif

      A0 x = a0;
      A0 q = nt2::abs(x);
      if(x < A0(-33.0))
      {
        A0 st = nt2::stirling(q);
        A0 p =  nt2::floor(q);
        bool iseven =  nt2::is_even((int32_t)p);
        if (p == q) return nt2::Nan<A0>();
        A0 z = q - p;
        if( z > nt2::Half<A0>() )
        {
          p += nt2::One<A0>();
          z = q - p;
        }
        z = q*nt2::sinpi(z);
        if( nt2::is_eqz(z) ) return nt2::Nan<A0>();
        st = nt2::Pi<A0>()/(nt2::abs(z)*st);
        return iseven  ? -st : st;
      }
      A0 z = nt2::One<A0>();
      while( x >= nt2::Three<A0>() )
      {
        x -= nt2::One<A0>();
        z *= x;
      }
      while( nt2::is_ltz(x) )
      {
        z /= x;
        x += nt2::One<A0>();
      }
      while( x < nt2::Two<A0>() )
      {
        if( nt2::is_eqz(x)) return nt2::Nan<A0>();
        z /= x;
        x +=  nt2::One<A0>();
      }
      if( x == nt2::Two<A0>() ) return(z);
      x -= nt2::Two<A0>();
      return z*details::gamma_kernel<A0>::gamma1(x);
    }
  };
} }

#endif
