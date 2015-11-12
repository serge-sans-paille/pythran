//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOTD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOTD_HPP_INCLUDED

#include <nt2/trigonometric/functions/acotd.hpp>
#include <nt2/include/functions/simd/atand.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/constants/_90.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/is_inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acotd_,tag::cpu_
                            , (A0)
                            , ((generic_<floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 z = nt2::_90<A0>()-nt2::if_else_zero(nt2::is_nez(a0),nt2::atand(nt2::abs(a0)));
      #ifndef BOOST_SIMD_NO_INFINITIES
      z = nt2::if_zero_else(nt2::is_inf(a0),z);
      #endif
      return nt2::b_or(z, nt2::bitofsign(a0));
    }
  };
} }


#endif
