//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOG1P_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOG1P_HPP_INCLUDED
#include <nt2/exponential/functions/log1p.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/seladd.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type u = oneplus(a0);
      result_type r = seladd(is_nez(u),
                             log(u),
                             (a0-minusone(u))/u); // cancels errors with IEEE arithmetic
      #ifndef BOOST_SIMD_NO_INFINITIES
      r = if_else(eq(u, Inf<A0>()),u, r);
      #endif
      return r;
    }
  };
} }

#endif
