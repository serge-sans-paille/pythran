//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_ERFCINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_ERFCINV_HPP_INCLUDED

#include <nt2/euler/functions/erfcinv.hpp>
#include <nt2/euler/functions/details/erfinv_kernel.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfcinv_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 a00 = oneminus(a0);
      A0 w = - log(a0*(Two<A0>()-a0));
      if (BOOST_UNLIKELY(w == Inf<A0>()))
      {
        return signnz(a00)*w;
      }
      else if ( w < 6.25)  // abs(a0) <  9.990343066500631e-01
      {
        w -= 3.125000;
        return a00*details::erfinv_kernel<A0>::erfinv1(w);
      }
      else if ( w < 16.000000 ) // abs(a0) <  9.999999437324111e-01
      {
        w = sqrt(w) - 3.250000;
        return a00*details::erfinv_kernel<A0>::erfinv2(w);
      }
      else
      {
        w = sqrt(w) - Five<A0>();
        return a00*details::erfinv_kernel<A0>::erfinv3(w);
      }
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfcinv_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    // This is taken from Approximating the erfcinv function of Mike Giles
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 a00 = oneminus(a0);
      A0 w = -log(a0*(Two<A0>()-a0));
      if (BOOST_UNLIKELY(w == Inf<A0>()))
      {
        return signnz(a00)*w;
      }
      else if ( w < Five<A0>() ) // abs(a00) <  9.966253323094464e-01
      {
        w -= single_constant<A0, 0x40200000> (); //2.500000f;
        return a00*details::erfinv_kernel<A0>::erfinv1(w);
      }
      else
      {
        w = sqrt(w);
        return copysign(details::erfinv_kernel<A0>::erfcinv2(w), a00);
      }
    }
  };
} }

#endif
