//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_SHR_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_SHR_HPP_INCLUDED

#include <boost/simd/bitwise/functions/shr.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/shift_right.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/assert.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shr_, tag::cpu_, (A0)(A1)(X)
                                   , ((simd_<arithmetic_<A0>,X>))
                                     (generic_< integer_<A1> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_unsigned<A0>::type ntype;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shr: a shift is out of range");
      return bitwise_cast<result_type>( bitwise_cast<ntype>(a0) >> a1 );
    }
  };
} } }

#endif
