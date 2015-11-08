//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_SCALE_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_SCALE_HPP_INCLUDED

#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/constants/maxexponent.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/shift_left.hpp>
#include <nt2/include/constants/nbmantissabits.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>

namespace nt2
{
  namespace details
  {
    template < class A0 >
    inline A0 scale(A0 const & y, const A0& k)
    {
      typedef typename nt2::meta::as_integer<A0>::type iA0;
      typedef typename nt2::meta::scalar_of<A0>::type sA0;
      iA0 ik =  toint(k);
      ik +=  Maxexponent<A0>();
      ik = shl(ik, Nbmantissabits<sA0>());
      return y*bitwise_cast<A0>(ik);;
    }
  }
}

#endif
