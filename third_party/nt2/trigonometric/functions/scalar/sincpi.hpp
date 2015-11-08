//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_SINCPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_SINCPI_HPP_INCLUDED

#include <nt2/trigonometric/functions/sincpi.hpp>
#include <nt2/include/functions/scalar/sinpi.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/simd/sdk/config.hpp>

#if !defined(BOOST_SIMD_NO_DENORMALS)
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/constants/eps.hpp>
#endif

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/constants/zero.hpp>
#endif
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sincpi_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      #if !defined(BOOST_SIMD_NO_INFINITIES)
      if(nt2::is_inf(a0)) return nt2::Zero<result_type>();
      #endif

      #if !defined(BOOST_SIMD_NO_DENORMALS)
      return (nt2::abs(a0) < nt2::Eps<result_type>()) ? nt2::One<result_type>()
                                                      : nt2::Invpi<result_type>()*nt2::sinpi(a0)/a0;
      #else
      return a0 ? nt2::Invpi<result_type>()*nt2::sinpi(a0)/a0
                : nt2::One<result_type>();
      #endif
    }
  };
} }

#endif
