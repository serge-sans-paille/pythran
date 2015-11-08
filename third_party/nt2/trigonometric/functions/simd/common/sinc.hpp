//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_SINC_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_SINC_HPP_INCLUDED

#include <nt2/trigonometric/functions/sinc.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/simd/sdk/config.hpp>

#if !defined(BOOST_SIMD_NO_DENORMALS)
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/constants/eps.hpp>
#endif

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinc_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type r1 =  nt2::sin(a0)/a0;

      #if !defined(BOOST_SIMD_NO_DENORMALS)
      r1 = nt2::if_else ( nt2::lt(nt2::abs(a0), nt2::Eps<A0>())
                        , nt2::One<A0>()
                        , r1
                        );
      #else
      r1 = nt2::if_else(nt2::is_eqz(a0), nt2::One<result_type>(), r1);
      #endif

      #if !defined(BOOST_SIMD_NO_INFINITIES)
      r1 = nt2::if_zero_else(nt2::is_inf(a0), r1);
      #endif

      return r1;
    }
  };
} }

#endif
