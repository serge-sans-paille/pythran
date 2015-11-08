//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_ERFC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_ERFC_HPP_INCLUDED

#include <nt2/euler/functions/erfc.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(nt2::is_nan(a0)) return a0;
      #endif
      A0 x =  nt2::abs(a0);
      A0 xx =  nt2::sqr(x);
      A0 z =  nt2::Zero<A0>();
      if(x <= A0(0.0000000001))
      {
        z = nt2::oneminus(x*nt2::Two<A0>()/nt2::sqrt(nt2::Pi<A0>()));
      }
      else if (x< A0(0.65))
      {
        z = nt2::oneminus(x*details::erf_kernel<A0>::erf1(xx));
      }
      else if(x< A0(2.2))
      {
        z = nt2::exp(-xx)*details::erf_kernel<A0>::erfc2(x);
      }
      else if(x< A0(6))
      {
        z = nt2::exp(-xx)*details::erf_kernel<A0>::erfc3(x);
      }
      return (a0 < 0.0) ? 2.0-z : z;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                              , (A0)
                              , ((scalar_<single_<A0> >))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x =  nt2::abs(a0);
      A0 r1 = nt2::Zero<A0>();
      A0 z =  x/oneplus(x);
      if (x < Twothird<A0>())
      {
        r1 = details::erf_kernel<A0>::erfc3(z);
      }
      #ifndef BOOST_SIMD_NO_INFINITIES
      else if (BOOST_UNLIKELY(x == Inf<A0>()))
      {
        r1 = Zero<A0>();
      }
      #endif
      else
      {
       z-= 0.4f;
        r1 = exp(-sqr(x))*details::erf_kernel<A0>::erfc2(z);
      }
      return (a0 < 0.0f) ? 2.0f-r1 : r1;
    }
  };

} }

#endif
