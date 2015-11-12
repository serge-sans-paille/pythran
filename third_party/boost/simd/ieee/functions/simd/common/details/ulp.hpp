//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_DETAILS_ULP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_DETAILS_ULP_HPP_INCLUDED

#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/predecessor.hpp>
#include <boost/simd/include/functions/simd/successor.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>

namespace boost{ namespace simd{ namespace details {

  template<class A0>
  inline A0 ulp(A0 const& a0)
  {
    A0 xp = boost::simd::predecessor(a0);
    A0 xs = boost::simd::successor(a0);
    return if_allbits_else( is_equal(a0, Inf<A0>())
                          , boost::simd::min(a0-xp,xs-a0)
                          );
  }

} } }

#endif
