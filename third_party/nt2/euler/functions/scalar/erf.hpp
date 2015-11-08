//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_ERF_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_ERF_HPP_INCLUDED

#include <nt2/euler/functions/erf.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/negif.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erf_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(a0)) return a0;
      #endif
      A0 x =  nt2::abs(a0);
      A0 xx = nt2::sqr(x);
      if(x<= A0(0.0000000001))
        return a0*nt2::Two<A0>()/nt2::sqrt(Pi<A0>());
      else if (x<= A0(0.65))
      {
        return a0*details::erf_kernel<A0>::erf1(xx);
      }
      else if(x<= A0(2.2))
      {
        A0 z = oneminus(exp(-xx)*details::erf_kernel<A0>::erfc2(x));
        return negif(is_ltz(a0), z);
      }
      else if(x<= A0(6))
      {
        A0 z = nt2::oneminus(exp(-xx)*details::erf_kernel<A0>::erfc3(x));
        return nt2::negif(nt2::is_ltz(a0), z);
      }
      else
        return nt2::One<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erf_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(a0)) return a0;
      #endif
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (nt2::is_inf(a0)) return signnz(a0);
      #endif
      A0 x =  nt2::abs(a0);
      if (x < Twothird<A0>())
      {
        return a0*details::erf_kernel<A0>::erf1(sqr(x));
      }
      else
      {
       A0 z = x/oneplus(x)-A0(0.4);
        A0 r2 =   oneminus(exp(-sqr(x))*details::erf_kernel<A0>::erfc2(z));
        if (a0 < Zero<A0>()) r2 = -r2;
        return r2;
      }

    }
  };
} }

#endif
